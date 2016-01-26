// dict.h
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

#ifndef __HAVE_DICT_H__
#define __HAVE_DICT_H__

#include "str.h"
#include "list.h"

typedef struct {
	size_t size;
	str* data[0];
} dict;	

dict* new_dict(size_t i);
void set(dict* d, str* k, str* v);
str* get(dict* d, str* k);
list* keys(dict* d);

#endif
