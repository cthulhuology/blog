// parse.c
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

////////////////////////////////////////////////////////////////////////////////
// headers
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
// functions

// between
//
// 	returns true if between min and max
//
int between(char n, char x, char c) {
	return (n <= c) && (c <= x);
}


// num
//
//	return true if this is a number
//
int num(char c) {
	return between('0','9',c);
}

// alpha
//
//	return true if this is a letter
//
int alpha(char c) {
	return between('a','z',c) || between('A','Z',c);
}

// alphanum
//
//	return true if this is a number or a letter
//
int alphanum(char c) {
	return alpha(c) || num(c);
}

// space
//
//	return true if this is a space
//
int space(char c) {
	return c == ' ';
}

// tab
//
//	return true if this is a tab
//
int tab(char c) {
	return c == '\t';
}

// nl
//
//	return true if this is a new line character
//
int nl(char c) {
	return c == '\n';
}

// cr
//
//	return true if this is a carriage return character
//
int cr(char c) {
	return c == '\r';
}

// whitespace
//
//	return true if this is whitespace
//
int whitespace(char c) {
	return space(c) || tab(c) || nl(c) || cr(c);
}

// colon
//
//	returns true if the character is a colon
//
int colon(char c) {
	return c == ':';
}

// semi
//
//	returns true if the character is a colon
//
int semi(char c) {
	return c == ';';
}
// slash
//
//	returns true if the character is a slash
//
int slash(char c) {
	return c == '/';
}

// dot
//
//	returns true if the character is a period
//
int dot(char c) {
	return c == '.';
}

// star
//
//	returns true if the character is an asterisk
//
int star(char c) {
	return c == '*';
}

// question
//
//	returns true if the character is a quesition mark
//
int question(char c) {
	return c == '?';
}

// lbracket
//
//	returns true if the character is a [
//
int lbracket(char c) {
	return c == '[';
}

// rbracket
//
//	returns true if the character is a ]
//
int rbracket(char c) {
	return c == ']';
}

// lsquigle
//
//	returns true if the character is a {
//
int lsquigle(char c) {
	return c == '{';
}

// rsquigle
//
//	returns true if the character is a }
//
int rsquigle(char c) {
	return c == '}';
}

// hex
//
//	return true if the character is 0-9 | a-f | A-F
int hex(char c) {
	return num(c) || between('a','f',c) || between('A','F',c);
}

// decimal
//
//	returns true if the character is a 0-9.
//
int decimal(char c ) {
	return num(c) || dot(c);
}

// ctrl
//
//	returns true if the character is 0-31, or 127
//
int ctrl(char c) {
	return between(0,31,c) || c == 127;
}

// crlf
//
//	returns 2 if the next 2 characters are \r\n
//	return 0 if they are not
//
int crlf(char* s) {
	if (s && s[0] && cr(s[0]) && nl(s[1])) return 2;
	return 0;
}

// eol
//
int eol(char* s) {
	return  crlf(s) | nl(s[0]) | !s[0];
}

// any
//
//	returns the length of any matching characters
//
int any(int (*test)(char), char* s) {
	int i = 0;
	while(s && s[i] && test(s[i])) ++i;
	return i;
}

// until
//
//	returns the length of characters until test
//
int until(int (*test)(char), char* s) {
	int i = 0;
	while(s && s[i] && !test(s[i])) ++i;
	return i;
}



// is
//
// 	returns length if string s is string x
// 	otherwise returns 0
//
int is(const char* x, char* s) {
	int i = strlen(x);
	if (strncmp(x,s,i)) return 0;
	return i;
}

// upto 
// 
// 	returns the length upto the matching string test
//
int upto(int (*test)(char*), char* s) {
	int i = 0;
	while (s && s[i] && !test(s+i)) ++i;
	return i;
}

// all
//
// 	tests if all the characters on a line match a test
//	if the whole line matches test then the length is returned
//	otherwise it returns 0
//
int all(int (*test)(char), char* s) {
	int i;
	int l = upto(eol, s);
	for (i = 0; i < l; ++i) {
		if (!s[i] || !test(s[i])) return 0;
	}
	return i;
}
