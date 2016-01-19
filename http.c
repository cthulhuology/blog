// http.c
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

// this file implements a minimal RFC2616 compliant protocol set for
// serving content over HTTP in the real world.

////////////////////////////////////////////////////////////////////////////////
// headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "http.h"
#include "str.h"

////////////////////////////////////////////////////////////////////////////////
// defines

////////////////////////////////////////////////////////////////////////////////
// globals

struct _request request;
struct _response response;

////////////////////////////////////////////////////////////////////////////////
// functions


// separator
//
//	returns true if the character is a HTTP separator
//
int separator(char c) {
	return  c == '(' ||
		c == ')' ||
		c == '<' ||
		c == '>' ||
		c == '@' ||
		c == ',' ||
		c == ';' ||
		c == ':' ||
		c == '\\' ||
		c == '"' ||
		c == '/' ||
		c == '[' ||
		c == ']' ||
		c == '?' ||
		c == '=' ||
		c == '{' ||
		c == '}' ||
		space(c) ||
		tab(c);
}

// terminator
//
// 	returns 1 if the character is a terminator for a token
// 	else 0

int terminator(char c) {
	return separator(c) || ctrl(c);
}

// token
// 
// 	returns the count of characters in the token
// 	returns 0 if no valid token
// 	
int token(char* s) {
	return until(terminator,s);
}

// method
//
// 	returns the length of the method or 0 
// 	
int method(char* s) {
	return token(s);		// extension-method must conform to token
}

// path
//
// 	returns the length of the path or 0
//
int path(char* s) {
	return until(space,s);
}

// version
//
// 	returns the length of the version string if it is a version string
// 	returns 0 otherwise
//
int version(char* s) {
	int i = 0;
	i += is("HTTP/",s);
	if (!i) return 0;
	i += any(decimal, s+i);
	return i;
}

// request_line
//
// 	parses the request line, populating:
// 		request.method
// 		request.path
// 		request.version
//
int request_line(char* s) {
	int v, p, m, i;
	i = any(whitespace,s);		// skip any leading whitespace
	m = method(s+i);		// grab the method
	request.method = ref(s+i,m);	// save a reference
	i += m;				// advance the pointer past the method
	i += any(whitespace,s+i);	// skip any whitespace (spec says just one sp)
	p = path(s+i);			// grap the path
	request.path = ref(s+i,p);	// save a refence
	i += p;				// advance the pointer past the path
	i += any(whitespace,s+i);	// skip any whitespace (spec says just one sp)
	v = version(s+i);		// grab the version
	request.version = ref(s+i,v);	// save a refence
	i += v;				// advance to eol
	return i;
}

// headers
//
// 	parses the headers if any populating:
// 		request.headers and request.header
//
int header(char* s) {
	int k, v, i;
	str* key;
	str* val;
	i = any(whitespace,s);		// if whitespace exists extend prior def
	if (i && request.headers > 0) {	// and we have a prior header
		v = upto(eol,s+i);
		request.header[(request.headers-1)*2+1]->length += v + i;	// extend it
		return i+v;		// and return the length to skip
	} 
	k = token(s+i);			// grab the key
	if (k == 0) return 0;		// if we have an empty line we're done!
	key = ref(s+i,k);		// save a reference
	i += k;				// advance pointer to separator	
	i += any(separator,s+i);	// skip any separators
	v = upto(eol,s+i);		// grab the remainder of the line
	val = ref(s+i,v);		// grab the value
	i += v;
	if (request.headers >= MAX_HEADERS) return i;	// just skip if maxed out
	request.header[request.headers*2] = key;
	request.header[request.headers*2+1] = val;
	++request.headers;		// increment the headers
	return i;		
}

void parse_request(str* s) {
	int i,h;
	i = request_line(s->data);	// parse the request line
	i += eol(s->data + i);	// advance to the next line
	while(i < s->length && (h = header(s->data + i))) {
		i += h;
		i += eol(s->data + i);
	}	// at this point i should point at the body, regardless
	request.body = ref(s->data + i, s->length - i);
}

void print_request() {
	int i;
	outs("Method: ",8);
	out(request.method);
	outs("\n",1);
	outs("Path: ",6);
	out(request.path);
	outs("\n",1);
	outs("Version: ",9);
	out(request.version);
	outs("\n",1);
	outs("Headers: (",10);
	outn(request.headers);
	outs(")\n",2);
	for( i = 0; i < request.headers; ++i) {
		outs("\t",1);
		out(request.header[i*2]);
		outs(": ",2);
		out(request.header[i*2 + 1]);
		outs("\n",1);
	}
	outs("Body:\n",6);
	out(request.body);
}

void clear_request() {
	int i;
	release(request.method);
	request.method = empty();
	release(request.path);
	request.path = empty();
	release(request.version);
	request.version = empty();
	release(request.body);
	request.body = empty();
	for (i = 0; i < request.headers; ++i) {
		release(request.header[i*2]);
		release(request.header[i*2+1]);
	}
	request.headers = 0;
	memset(&request.header,0,sizeof(request.header));
}

void sp() {
	outs(" ",1);
}

void endl() {
	outs("\n",1);
}

void clear_response() {
	response.version = empty();
	response.code = empty();
	response.reason = empty();
	response.headers = 0;
	response.body = empty();
	memset(&response.header,0,sizeof(response.header));
}

void response_line() {
	if (!response.version->length && !response.code->length && !response.reason->length) {
		outs("HTTP/1.1 200 OK\n",16);
		return;
	}
	out(response.version);
	sp();
	out(response.code);
	sp();
	out(response.reason);
	endl();
}

void response_headers() {
	int i;
	if (!response.headers) {
		outs("Content-Length: ",16);
		out(strnum(response.body->length));
		endl();
		outs("Connection: close",17);
		endl();
		endl();
		return;
	}
	for(i = 0; i < response.headers; ++i) {
		out(response.header[i*2]);
		out(response.header[i*2+1]);
		endl();
	}
	endl();
}

void response_body() {
	out(response.body);
}

void respond() {
	response_line();
	response_headers();
	response_body();		
}

// don't compile main if we're in test mode
#ifndef TEST

// main 
//
int main (int argc, char** argv) {
	str* buffer = in();		// read the initial request in
	clear_request();		// ensure request is clear
	clear_response();		// ensure response is clear
	parse_request(buffer);		// parse the initial request
	respond();
	return 0;
}

#endif
