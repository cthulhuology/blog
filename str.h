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
#include <stdlib.h>

typedef struct {
	char* data;
	size_t length;	
	char buffer[0];
} str;

str* allot(int len);
str* ref(char* data, int len);
int out(str* s);
str* in();
void release(str* s);

#endif
