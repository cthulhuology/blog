// file.c
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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "file.h"


str* read_file(str* filename) {
	str* s;
	struct stat fs;
	size_t fd, i = 0;

	if (stat(filename->data,&fs)) return empty();	// if the file don't exist empty

	if (!fs.st_size) return empty();	// return empty if file empty
	
	fd = open(filename->data,O_RDONLY);		// readonly fd
	if (fd < 0) return empty();
	
	s = allot(fs.st_size);			// a buffer the size of the file
	
	while ( i < fs.st_size) {
		i += read(fd,s->data + i, fs.st_size - i);
	}

	return s;
}

int input(str* filename) {
	struct stat fs;
	size_t fd;
	if (stat(filename->data,&fs)) return -1;
	fd = open(filename->data,O_RDONLY);
	return fd;
}

int output(str* filename) {
	size_t fd;
	fd = open(filename->data,O_WRONLY|O_CREAT|O_TRUNC,0600);
	return fd;

}

int exists(str* filename) {
	struct stat fs;
	if (stat(filename->data,&fs)) return 0;
	return S_ISREG(fs.st_mode);	// should be a regular file
}
