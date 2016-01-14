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

////////////////////////////////////////////////////////////////////////////////
// defines

////////////////////////////////////////////////////////////////////////////////
// globals

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
		|| space(c)
		|| tab(c);
}

int terminator(char c) {
	return separator(c) || ctrl(c);
}

// token
// 
// 	returns the count of characters in the token
// 	returns 0 if no valid token
// 	
int token(char *s) {
	return until(terminator,s);
}

// method
//
// 	returns the length of the method or 0 
// 	
int method(char *s) {
	return token(s);		// extension-method must conform to token
}

// path
//
// 	returns the length of the path or 0
//
int path(char *s) {
	return until(space,s);
}

// version
//
// 	returns the length of the version string if it is a version string
// 	returns 0 otherwise
//
int version(char *s) {
	int i = 0;
	i += is("HTTP/",s);
	if (!i) return 0;
	i += any(decimal, s+i);
	return i;
}

int request_line(char* s) {
	int i = 0;
	i += method(s);
	if (!space(s[i])) return 0;
	i = path(&s[i+1]);
	if (!space(s[i])) return 0;
	i += version(&s[i+1]);
	if (!clrf(&s[i]) || nl(s[i])) return 0;
	i += crlf(&s[i]) + nl(s[i]);
	return
}

int end_of_headers(char* s) {
	int i = 0;
	if (i = eol(s)) 
		if(i += eol(s+i))
			return i;
	return 0;
}

// main 
//
int main (int argc, char** argv) {
	printf("HTTP/1.1 200 OK\nContent-Length:11\n\nhello world");
	return 0;
}
