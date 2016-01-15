// test.c
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

////////////////////////////////////////////////////////////////////////////////
// headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int passed = 0;
int failed = 0;
int skipped = 0;

void ok(int result, char* test) {
	if (!test) {
		++skipped;
		return;
	}
	if (result) {
		printf("ok %s\n", test);
		++passed;
		return;
	}
	printf("failed %s\n", test);
	++failed;
}

void fail(int result, char* test) {
	if (!test) {
		++skipped;
		return;
	}
	if (!result) {
		printf("ok %s\n", test);
		++passed;
		return;
	}
	printf("failed %s\n", test);
	++failed;
}

void value(int expect, int result, char* test) {
	if (!test) {
		++skipped;
		 return;
	}
	if (expect == result) {
		printf("ok %s\n", test);
		++passed;
		return;
	}
	printf("failed %s expected: %d got: %d\n", test, expect, result);
	++failed;
}

int done(const char* tests) {
	printf("--------------------------------------------------------------------------------\n");
	printf("%s:\n", tests);
	printf("tests:\t\t%8d\n", passed + failed + skipped);
	printf("passed:\t\t%8d\n", passed);
	printf("failed:\t\t%8d\n", failed);
	printf("skipped:\t%8d\n", skipped);
	printf("--------------------------------------------------------------------------------\n");
	return 0;
}
