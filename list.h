// list.h
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


#ifndef __HAVE_LIST_H__
#define __HAVE_LIST_H__

#include "str.h"

typedef struct {
	size_t start;
	size_t end;
	size_t size;
	str* data[0];
} list;	

list* new_list(size_t i);
void push(list* l, str* s);
str* pop(list* l);
list* each(list* l, void(*op)(str* s));
list* map(list* l, str*(*op)(str* s));
void release_list(list* l);
list* sort(list* l);

#endif
