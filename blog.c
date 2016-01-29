// blog.c
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

str* www(str* s) {
	return concat(ref("./www/",6),s);
}

void respond_304(str* p, str* e) {
	fprintf(stderr,"respond 304 %s etag: %s\n", p->data, e->data);
	response.version = ref("HTTP/1.1",8);
	response.code = ref("304",3);
	response.reason = ref("Not Modified",12);
	response.body = empty();
	respond();
}

void respond_200(str* p, str* e) {
	fprintf(stderr,"respond 200 %s etag: %s\n", p->data, e->data);
	response.body = read_file(p);
	response.header[0] = ref("Content-Length",14);
	response.header[1] = strnum(response.body->length);
	response.header[2] = ref("Connection",10);
	response.header[3] = ref("close",5);
	response.header[4] = ref("ETag",4);
	response.header[5] = e;
	response.header[6] = ref("Cache-Control",13);
	response.header[7] = ref("public, max-age=86400",21);
	response.headers = 4;
	respond();
}

#ifdef BLOG

int main(int argc, char** argv) {
	int f;
	str* p;
	str* e;
	str* indexp = ref("./www/index.html",16);
	str* buffer = in();		// read the initial request in
//	fprintf(stderr,"%s\n", buffer->data);
	clear_request();		// ensure request is clear
	clear_response();		// ensure response is clear
	parse_request(buffer);		// parse the initial request
	p = www(request.path);
	f = exists(p);
	e = etag(f ? p : indexp);
	if (not_modified(e)) respond_304(p, e);
	else respond_200(f ? p : indexp, e);
	return 0;
}

#endif
