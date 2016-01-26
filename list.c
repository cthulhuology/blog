// list.c
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


#include <stdlib.h>
#include "list.h"
#include "str.h"

list* new_list(size_t i) {
	list* l;
	if (i < 2) return NULL;
	l = (list*)malloc(sizeof(list) + sizeof(str*)*i);	
	l->start = 0;
	l->end = 0;
	l->size = i;
}

void push(list* l, str* s) {	// push a value on the end
	if (!l) return;
	l->data[l->end++ % l->size] = s;
} 

str* shift(list* l) {	// pop a string off the front
	if (!l) return;
	return l->data[l->start++ % l->size];
}

str* pop(list* l) {	// pop a string off the end
	if (!l) return;
	return l->data[--l->end % l->size];	
}

list* each(list* l, void(*op)(str* s)) {
	int i;
	if (!l) return;
	for (i = l->start; i != l->end; ++i)
		op(l->data[i % l->size]);
}

list* map(list* l, str*(*op)(str* s)) {
	int i;
	if (!l) return NULL;
	list* l2 = new_list(l->size);
	for (i = l->start; i != l->end; ++i)
		push(l2, op(l->data[i % l->size]));
	return l2;
}

int length(list* l) {
	if (!l) return 0;
	return l->end - l->start;
}

list* sort(list* l) {
	qsort(l->data, l->end - l->start, sizeof(str*),(__compar_fn_t)sortorder);
	return l;
}

void release_list(list* l) {
	free(l);
}
