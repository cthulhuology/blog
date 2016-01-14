// str.c
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

#include <unistd.h> 
#include <string.h>
#include "str.h"

// out
//
// 	writes a string out to the given stdout
//
int out(str* s) {
	write(1,s->data,s->length);
}

// in
//
// 	reads string from stdin
//
str* in() {
	str* retval = (str*)malloc(sizeof(str));
	retval->data = (char*)malloc(4096);
	retval->length = read(0, retval->data, 4096);
	return retval;
}

// release
//
// 	frees the string and it's memory
//
void release(str* s) {
	if (s && s->data) free(s->data);
	if (s) free(s);
}
