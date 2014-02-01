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


#ifndef HANDLER_H
#define HANDLER_H
#define _GNU_SOURCE
#include "account.h"
#include "message.h"
#include "connection.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef int (*handler)(struct irc_message_t*);
handler* handlers;

void bt_setupHandlers();
void bt_handle(struct irc_message_t *msg);
int bt_handlePrivMsg(struct irc_message_t* msg);
int bt_handleNumeric(struct irc_message_t* msg);
int bt_handlePing(struct irc_message_t* msg);
int bt_defaultHandler(struct irc_message_t* msg);
#endif
