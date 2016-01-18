// http.h
//
// Copyright (C) 2016 David J. Goehrig
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.
// You should have received a copy of the GNU Affero General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//

#ifndef __HAVE_HTTP_H__
#define __HAVE_HTTP_H__

#include "str.h"

// define a maximum number of header rows we're willing to consider
#ifndef MAX_HEADERS
#define MAX_HEADERS 512
#endif

int separator(char c);
int terminator(char c);
int token(char* s);
int method(char* s);
int path(char* s);
int version(char* s);
int request_line(char* s);
void respond();
void sp();

extern struct _request {
	str* method;
	str* path;
	str* version;
	int headers; 
	str* header[MAX_HEADERS*2];	// we store them key, value in pairs
	str* body;
} request;

extern struct _response {
	str* version;
	str* code;
	str* reason;
	int headers;
	str* header[MAX_HEADERS*2];
	str* body;	
} response;


#endif

