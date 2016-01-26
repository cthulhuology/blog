// dir.c
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

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "str.h"
#include "list.h"

int mkpath(str* p) {
	int i = 0;
	for (i = 0; i < p->length; ++i) {
		if (p->data[i] != '/') continue;
		p->data[i] = '\0';
		mkdir(p->data,0777);
		p->data[i] = '/';
	}
	return p->length;
}

list* listpath(str* p) {
	struct stat fs;
	DIR* d; 
	struct dirent* dr;
	list* l = new_list(32);
	if (stat(p->data,&fs)) return NULL;
	if (!S_ISDIR(fs.st_mode)) return NULL;
	d = opendir(p->data);
	while (dr = readdir(d)) {
		if (!strncmp(dr->d_name,".",1)) continue;
		push(l,copy(dr->d_name,strlen(dr->d_name)));
	}
	closedir(d);
	return l;
}

str* path(list* l) {
	int i;
	size_t ll = 0;
	size_t n = 0;
	str* s;
	for (i = l->start; i < l->end; ++i) n += l->data[i%l->size]->length + 1;
	s = allot(n);
	n = 0;
	for (i = l->start; i < l->end; ++i) {
		memcpy(s->data + n, l->data[i%l->size]->data, l->data[i%l->size]->length);
		n += l->data[i%l->size]->length;
		s->data[n++] = '/';
	}
	s->data[n] = '\0';
	return s;
}

#ifdef DIRTOOLS 

void outln(str* s) {
	out(s);
	outs("\n",1);	
}

int main(int argc, char** argv) {
	if (argc != 2) return 0;
	if (!strcmp("./mkpath",argv[0])) mkpath(argv[1]);
	if (!strcmp("./lspath",argv[0])) each(sort(listpath(argv[1])), outln);
	return 0;
}

#endif
