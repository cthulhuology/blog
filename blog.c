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

void redir(str* p) {
	response.version = ref("HTTP/1.1",8);
	response.code = ref("301",3);
	response.reason = ref("Moved Permanently",17);
	response.headers++;
	response.header[0] = ref("Location",8);
	response.header[1] = ref("/index.html",11);
	respond();
}

#ifdef BLOG

int main(int argc, char** argv) {
	str* p;
	str* buffer = in();		// read the initial request in
	clear_request();		// ensure request is clear
	clear_response();		// ensure response is clear
	parse_request(buffer);		// parse the initial request
	p = www(request.path);
	if (exists(p)) {
		response.body = read_file(www(request.path));
		respond();
	} else {
		redir(p);
	}
	return 0;
}

#endif
