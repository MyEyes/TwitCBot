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
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "account.h"
#include "bot.h"
#include "connection.h"
#include "message.h"
#include "handler.h"

void error(const char *msg)
{
	fprintf(stderr, "ERROR, %s\n", msg);
	perror("");
	exit(-1);
}

void warning(const char *msg)
{
	fprintf(stderr, "WARNING, %s\n", msg);
}

int main(int argc, char*argv[])
{
	printf("Starting Firzberrybot v%d.%d\n",ver_major,ver_minor);
	bt_setupHandlers();
	bt_connect(servername, serverport);
	char* message = malloc(sizeof(char)*1024);
	sprintf(message, "PASS %s\r\n", password);
	bt_send(message);
	sprintf(message, "NICK %s\r\n", username);
	bt_send(message);
	sprintf(message, "JOIN #firzen14\r\n");
	bt_send(message);
	while(1)
		;
	return 0;
}
