/********************************************************************************
* The MIT License (MIT)
*
* Copyright (c) 2014 Nils Ole Timm
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
* the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*********************************************************************************/


#include "handler.h"

void bt_setupHandlers()
{
	handlers = malloc(20*sizeof(int (*)(struct irc_message_t*)));
	int x=0;
	for(x=0; x<20; x++)
		handlers[x]=0;
	handlers[PRIVMSG]=bt_handlePrivMsg;
	handlers[NUMERIC]=bt_handleNumeric;
	handlers[PING]=bt_handlePing;
}

void bt_handle(struct irc_message_t *msg)
{
	if(msg->Type>=0 && msg->Type<20 && handlers[msg->Type]>0)
	{
		handlers[msg->Type](msg);
	}
	else
	{
		bt_defaultHandler(msg);
	}
}

int bt_checkCommand(char*sender, char* room, char* input)
{
	if(strstr(input, "!test"))
	{
		bt_sendRoom(room, "Yay");
		return 1;
	}
	if(strstr(input, "!Info"))
	{
		char* msg;
		asprintf(&msg, "This is FirzberryPiBot v%d.%d by Firzen14",ver_major,ver_minor); 
		bt_sendRoom(room, msg);
		free(msg);
		return 1;
	}
	return 0;
}

int bt_handlePrivMsg(struct irc_message_t *msg)
{
	char* shortSender = 0;
	char* room = 0;
	sscanf(msg->Sender,"%m[^!]",&shortSender);
	sscanf(msg->Parameters, "%ms", &room);
	bt_checkCommand(shortSender, room, msg->LongParameter);
	free(shortSender);
	free(room);
	return 0;
}

int bt_handleNumeric(struct irc_message_t *msg)
{
	return 0;
}

int bt_handlePing(struct irc_message_t *msg)
{
	char* message;
	printf("PING\n");
	asprintf(&message, "PONG %s\r\n", msg->Parameters);
	bt_send(message);
	free(message);
	return 0;
}

int bt_defaultHandler(struct irc_message_t *msg)
{
	printf("Messagetype: %s UNHANDLED\n", bt_msgTypeToString(msg->Type));
	return 0;
}
