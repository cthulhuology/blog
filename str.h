// str.h
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

#ifndef __HAVE_STR_H__
#define __HAVE_STR_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char* data;
	size_t length;	
	char buffer[0];
} str;

str* allot(int len);
str* ref(char* data, int len);
str* copy(char* data, int len);
int out(const str* s);
int outs(const char* s, int i);
int outn(int i );
str* in();
void release(str* s);
str* strnum(int i);
str* empty();
int sortorder(str** a, str** b);
int hash(str* s);
int eq(str* a, str* b);
str* concat(str* a, str* b);

#endif
