// dict.c
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
#include "dict.h"
#include "list.h"
#include "str.h"

dict* new_dict(size_t i) {
	dict* d;
	if (i < 2) return NULL;
	d = (dict*)malloc(sizeof(dict) + sizeof(str*)*i*2);
	d->size = i;
	return d;	
}

void set(dict* d, str* k, str* v) {
	int i;
	int h = hash(k);
	for (i = 0; i < d->size; ++i) {
		if (d->data[((i+h)%d->size)*2] && !eq(k,d->data[((i+h)%d->size)*2])) continue;
		d->data[((i+h)%d->size)*2] = k;
		d->data[((i+h)%d->size)*2 + 1] = v;
		return;
	}
	return;	
}

str* get(dict* d, str* k) {
	int i;
	int h = hash(k);
	for (i = 0; i < d->size; ++i) {
		if (d->data[((i+h)%d->size)*2] && !eq(k,d->data[((i+h)%d->size)*2])) 
			continue;
		if (!d->data[((i+h)%d->size)*2]) return empty();
		return d->data[((i+h)%d->size)*2 + 1];
	}
	return empty();
}

list* keys(dict* d) {
	int i;
	list* l = new_list(d->size);
	for (i = 0; i < d->size; ++i) 
		if (d->data[i*2]) push(l,d->data[i*2]);
	return l;
}

