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


#ifndef MESSAGE_H
#define MESSAGE_H
enum messagetype_t
{
	NICK,
	PASS,
	NOTICE,
	PRIVMSG,
	JOIN,
	NUMERIC,
	PING,
	PONG,
	PART,
	HISTORYEND,
	MODE,
	EMOTESET,
	USERCOLOR
};

struct irc_message_t
{
	enum messagetype_t 	Type;
	int			Numeric;
	char* 			Sender;
	char*			Parameters;
	char*			LongParameter;
	int			ByteLength;
};

struct irc_message_t* 	bt_decodeMessage(char* input);
char*			bt_encodeMessage(struct irc_message_t* input);
void			bt_printMessage(struct irc_message_t* msg);
void			bt_freeMessage(struct irc_message_t* msg);
enum messagetype_t	bt_msgTypeFromString(char* str);
const char*		bt_msgTypeToString(enum messagetype_t type);
int			bt_measureMsgLength(struct irc_message_t* msg);
#endif
