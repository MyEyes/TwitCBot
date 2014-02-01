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
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include "bot.h"
#include "connection.h"
#include "message.h"
#include "handler.h"

int bt_connect(const char* hostname, int port)
{
	printf("Resolving host\n");
	server = gethostbyname(hostname);
	if(server==NULL)
	{
		error("Could not find host");
	}
	printf("Opening socket\n");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		error("Could not open socket");
	}
	printf("Connecting\n");
	bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char*)server->h_addr,
		(char*)&serv_addr.sin_addr.s_addr,
		server->h_length);
	serv_addr.sin_port = htons(port);
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) <0)
	{
		error("Could not connect");
	}
	connected = 1;
	printf("Starting receive thread\n");
	pthread_create(&receiveThread, NULL, bt_receive, NULL);
	return 0;
}

int bt_send(char* message)
{
	if(!connected)
		return -1;
	//printf("Sending message: %s", message);
	int n = write(sockfd, message, strlen(message));
	if(n<0)
		error("Could not send");
	return 0;
}

int bt_sendRoom(char* room, char* msg)
{
	char* message = malloc(sizeof(char)*1024);
	sprintf(message, "PRIVMSG %s :%s\r\n",room,msg);
	bt_send(message);
	free(message);
	return 0;
}

void* bt_receive(void* defp)
{
	int n;
	int overflow=0;
	while((n = read(sockfd, buffer+overflow, 1024)>0))
	{
		n=1024;
		int offset=0;
		int x=0;
		for(x=0; x<n+overflow; x++)
		{
			if(buffer[x]=='\n')
			{
				struct irc_message_t* msg = bt_decodeMessage(buffer+offset);
				//bt_printMessage(msg);
				bt_handle(msg);
				bt_freeMessage(msg);
				offset=x+1;
			}
			else if(buffer[x]==0)
				break;
		}
		memcpy(buffer, buffer+offset, x-offset);
		memset(buffer+x-offset, 0, sizeof(char)*(2048-offset));
		overflow=x-offset;
	}
	return NULL;
}

int bt_disconnect()
{
	printf("Disconnecting\n");
	close(sockfd);
	return 0;
}
