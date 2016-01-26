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

#include "str.h"
#include "html.h"
#include "http.h"
#include "file.h"
#include <limits.h>


char _www_path[PATH_MAX];
char* www(str* s) {
	memcpy(_www_path,"./www/",6);
	memcpy(_www_path+6,s->data,s->length);
	_www_path[s->length + 6 ] = '\0';
	return _www_path;
}

char _content_path[PATH_MAX];
char* content(str* s) {
	memcpy(_content_path,"./content/",10);
	memcpy(_content_path+10,s->data,s->length);
	_content_path[s->length + 10] = '\0';
	return _content_path;
}


#ifdef BLOG

int main(int argc, char** argv) {
	str* buffer = in();		// read the initial request in
	clear_request();		// ensure request is clear
	clear_response();		// ensure response is clear
	parse_request(buffer);		// parse the initial request
	response.body = read_file(www(request.path));
	respond();
	return 0;
}

#endif
