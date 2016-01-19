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

// allot
//
// 	allocates a string of a given size
//
str* allot(int len) {
	str* s = (str*)malloc(sizeof(str) + len);
	s->length = (size_t)len;
	s->data = s->buffer;	
	return s;
}

// ref
//
// 	creates a string that refers to another
//

str* ref(char* data, int len) {
	str* s = (str*)malloc(sizeof(str));
	s->data = data;
	s->length = (size_t)len;
	return s;
}

// out
//
// 	writes a string out to the given stdout
//
int out(const str* s) {
	write(1,s->data,s->length);
}

// outs
//
// 	writes a static string
//
int outs(const char* s, int i) {
	write(1,s,i);
}

// outn
//
// 	writes an integer out
//
int outn(int i) {
	char buffer[16];
	int l = snprintf(buffer,16,"%ld",i);	
	write(1,bufffer,l);
}

// in
//
// 	reads string from stdin
//
str* in() {
	str* s = (str*)malloc(sizeof(str) + 4096);
	s->data = s->buffer;
	s->length = read(0, s->data, 4096);
	return s;
}

// release
//
// 	frees the string 
//
void release(str* s) {
	if (s) free(s);
}

// strnum
// 
// 	returns a string version of a number
// 	use immediately or it might be mutated
//
str* strnum(int i) {
	str* _numstr = allot(16);
	_numstr->length = snprintf(_numstr->buffer,16,"%ld",i);
	return _numstr;
}

// empty
//
str* empty() {
	return ref(NULL,0);
}
