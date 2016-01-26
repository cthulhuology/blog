// generate.c
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

#include <limits.h>
#include "str.h"
#include "list.h"
#include "dir.h"
#include "generate.h"

list* _path;

void create_post(str* post) {
	out(path(_path));
	out(post);
	outs("\n",1);
}

void dir_posts(str* day) {
	push(_path,day);
	list* posts = sort(listpath(path(_path)));
	each(posts, create_post);
	pop(_path);
}

void dir_days(str* month) {
	push(_path,month);
	list* days = sort(listpath(path(_path)));
	each(days,dir_posts);
	pop(_path);
}

void dir_month(str* year) {
	push(_path,year);
	list* months = sort(listpath(path(_path)));
	each(months,dir_days);
	pop(_path);
}

void dir_year() {
	push(_path, ref("./content",9));
	list* years = sort(listpath(path(_path)));
	each(years,dir_month);
	pop(_path);
}



#ifdef GENERATE

int main(int argc, char** argv) {
	_path = new_list(16);
	dir_year();
	return 0;
}

#endif
