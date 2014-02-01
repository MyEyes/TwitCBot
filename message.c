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


#include <stdio.h>
#include <stdlib.h>
#include "message.h"
#include <string.h>

struct irc_message_t* bt_decodeMessage(char* input)
{
	struct irc_message_t* message = (struct irc_message_t*) malloc(sizeof(struct irc_message_t));
	message->Numeric=-1;
	message->LongParameter=NULL;
	message->Parameters=NULL;
	message->Sender=NULL;
	char *typestring = NULL;
	int n = sscanf(input, ":%ms %ms %m[^\r^\n]", &(message->Sender), &typestring, &(message->Parameters));
	if(n<3)
	{
		if(n>0)
		{
			free(typestring);
			free(message->Sender);
			free(message->Parameters);
		}
		n = sscanf(input, "%ms %m[^\r^\n]", &typestring, &(message->Parameters));
	}
	sscanf(message->Parameters,"%*[^:] :%m[^:]",&(message->LongParameter));
	message->Type=bt_msgTypeFromString(typestring);
	if(message->Type==NUMERIC)
	{
		sscanf(typestring, "%d", &(message->Numeric));
	}
	free(typestring);
	message->ByteLength=bt_measureMsgLength(message);
	return message;
}

int bt_measureMsgLength(struct irc_message_t* msg)
{
	int len = 0;
	if(msg->Sender)
		len+=1+strlen(msg->Sender)+1; 		//:Sender
	if(msg->Type!=NUMERIC)
		len+=strlen(bt_msgTypeToString(msg->Type));
	else
		len+=3;
	if(msg->Parameters)
		len+=1+strlen(msg->Parameters);		// Parameters
	len+=2;					//\r\n
	return len;
}

char* bt_encodeMessage(struct irc_message_t* input)
{
	return NULL;
}

void bt_printMessage(struct irc_message_t* msg)
{
	printf("Message:\n\tBytes:\t\t%d\n\tType: \t\t%d\n\tNumeric: \t%d\n\tSender: \t%s\n\tParams: \t%s\n\tLong Param: \t%s\n", msg->ByteLength,msg->Type,msg->Numeric,msg->Sender,msg->Parameters,msg->LongParameter);
}

void bt_freeMessage(struct irc_message_t* msg)
{
	free(msg->Sender);
	free(msg->Parameters);
	if(msg->LongParameter>0)
		free(msg->LongParameter);
	free(msg);
}

enum messagetype_t bt_msgTypeFromString(char* str)
{
	int value=0;
	if(sscanf(str, "%d", &value)>0)
		return NUMERIC;
	if(strcmp(str, "NOTICE")==0)
		return NOTICE;
	if(strcmp(str, "PRIVMSG")==0)
		return PRIVMSG;
	if(strcmp(str, "NICK")==0)
		return NICK;
	if(strcmp(str, "JOIN")==0)
		return JOIN;
	if(strcmp(str, "PASS")==0)
		return PASS;
	if(strcmp(str, "JOIN")==0)
		return JOIN;
	if(strcmp(str, "PING")==0)
		return PING;
	if(strcmp(str, "USERCOLOR")==0)
		return USERCOLOR;
	if(strcmp(str, "EMOTESET")==0)
		return EMOTESET;
	if(strcmp(str, "MODE")==0)
		return MODE;
	return -1;
}

const char* bt_msgTypeToString(enum messagetype_t type)
{
	switch(type)
	{
		case NOTICE:
			return "NOTICE";
		case PRIVMSG:
			return "PRIVMSG";
		case JOIN:
			return "JOIN";
		case PART:
			return "PART";
		case PONG:
			return "PONG";
		case MODE:
			return "MODE";
		case HISTORYEND:
			return "HISTORYEND";
		case USERCOLOR:
			return "USERCOLOR";
		case EMOTESET:
			return "EMOTESET";
		default:
			return "UNKNOWN";
	};
}
