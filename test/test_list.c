// test_list.c
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

#include "test.h"
#include "list.h"
#include "str.h"

// This is the main test progie for the list

int main(int argc, char** argv) {

	list* l;
	str* a = ref("hello",5);
	str* b = ref("world",5);

	ok(NULL == new_list(0), "allocate an empty list");	
	ok(NULL == new_list(1), "allocate a list with one element");
	ok(NULL != (l = new_list(2)), "allocate a list with two elements");
	value(2, l->size, "test the size of the list");	
	value(0, l->start, "test the start position");	
	value(0, l->end, "test the start position");	
	push(l,a);
	value(0, l->start, "test pushing start value");
	value(1, l->end, "test pushing end value");
	value(1, length(l), "has one element");
	push(l,b);
	value(0, l->start, "test pushing second  start value");
	value(2, l->end, "test pushing second end value");
	value(2, length(l), "has one element");
	ok(a == shift(l), "shift a");
	value(1, length(l), "has one element");
	ok(b == shift(l), "shift b");
	value(0, length(l), "has one element");
	ok(a == shift(l), "shift a again");
	value(-1, length(l), "has negative one elements");
	
	return done("test_list");
}
