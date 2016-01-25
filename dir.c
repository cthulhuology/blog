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

int mkpath(char* path) {
	size_t l = strlen(path);
	int i = 0;
	for (i = 0; i < l; ++i) {
		if (path[i] != '/') continue;
		path[i] = '\0';
		mkdir(path,0777);
		path[i] = '/';
	}
	return l;
}

list* listpath(char* path) {
	struct stat fs;
	DIR* d; 
	struct dirent* dr;
	list* l = new_list(32);
	if (stat(path,&fs)) return NULL;
	if (!S_ISDIR(fs.st_mode)) return NULL;
	d = opendir(path);
	while (dr = readdir(d)) {
		if (!strncmp(dr->d_name,".",1)) continue;
		push(l,ref(dr->d_name,strlen(dr->d_name)));
	}
	closedir(d);
	return l;
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
