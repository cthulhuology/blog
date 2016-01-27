// parse.h
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

#ifndef __HAVE_PARSE_H__
#define __HAVE_PARSE_H__

int between(char n, char x, char c);
int num(char c);
int alpha(char c);
int alphanum(char c);
int space(char c);
int tab(char c);
int nl(char c);
int cr(char c);
int whitespace(char c);
int hs(char c);
int colon(char c);
int semi(char c);
int slash(char c);
int dot(char c);
int star(char c);
int question(char c);
int lbracket(char c);
int rbracket(char c);
int bar(char c);
int lsquigle(char c);
int rsquigle(char c);
int hex(char c);
int decimal(char c );
int ctrl(char c);
int crlf(char* s);
int eol(char* s);
int any(int (*test)(char), char* s);
int until(int (*test)(char), char* s);
int is(const char* x, char* s);
int upto(int (*test)(char*), char* s);
int all(int (*test)(char), char* s);

#endif
