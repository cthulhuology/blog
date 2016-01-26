// test_dict.c
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
#include "dict.h"
#include "list.h"
#include "str.h"


// This is the main test progie for the dict

int main(int argc, char** argv) {
	
	list* l;
	dict* d;
	str* a = ref("hello",5);
	str* b = ref("world",5);
	str* c = ref("foobar",6);

	ok(NULL == new_dict(0), "allocate an empty dict");
	ok(NULL == new_dict(1), "allocate a dict with element");
	ok(NULL != (d = new_dict(2)), "allocate a dict with two element");
	value(2, d->size, "test the size of the dict");
	set(d,a,b);
	ok(eq(empty(),get(d,b)), "fetch an empty result");
	ok(b == get(d,a), "fetch the key a ");
	set(d,b,a);
	ok(a == get(d,b), "fetch key of b");
	set(d,c,a);
	done("test_dict");
}
