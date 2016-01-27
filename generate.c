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
#include "file.h"
#include "worker.h"
#include <stdlib.h>

list* _in_path;
list* _out_path;

void create_post(str* post) {
	char* args[] = { NULL };
	str* s = allot(post->length+2);
	str* outpath = path(_out_path);
	str* infile = concat(path(_in_path),post);
	str* outfile;

	memcpy(s->data,post->data,post->length -2);
	memcpy(s->data + post->length - 2, "html", 4);	
	outfile = concat(outpath,s);

	mkpath(outpath);
	run("./md", input(infile), output(outfile), args);
}

void dir_posts(str* day) {
	push(_in_path,day);
	push(_out_path,day);
	list* posts = sort(listpath(path(_in_path)));
	each(posts, create_post);
	pop(_in_path);
	pop(_out_path);
}

void dir_days(str* month) {
	push(_in_path,month);
	push(_out_path,month);
	list* days = sort(listpath(path(_in_path)));
	each(days,dir_posts);
	pop(_in_path);
	pop(_out_path);
}

void dir_month(str* year) {
	push(_in_path,year);
	push(_out_path,year);
	list* months = sort(listpath(path(_in_path)));
	each(months,dir_days);
	pop(_in_path);
	pop(_out_path);
}

void dir_year() {
	push(_in_path, ref("./content",9));
	push(_out_path, ref("./www",5));
	list* years = sort(listpath(path(_in_path)));
	each(years,dir_month);
	pop(_in_path);
	pop(_out_path);
}

void indexes() {
	char* args[] = { NULL };
	run("./md",input(ref("./nav.md",8)),output(ref("./www/index.html",16)),args);
}

#ifdef GENERATE

int main(int argc, char** argv) {
	_in_path = new_list(16);
	_out_path = new_list(16);
	dir_year();
	indexes();
	reap();
	return 0;
}

#endif
