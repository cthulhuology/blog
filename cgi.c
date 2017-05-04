// cgi.c
//
// Copyright (C) 2017 David J. Goehrig
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

#include <unistd.h>
#include <stdio.h>

char *envars[] = {
	"AUTH_TYPE" , 		// "Basic" | "Digest"
	"CONTENT_LENGTH" ,	// 123
	"CONTENT_TYPE" , 	// text/plain
	"GATEWAY_INTERFACE",	// "CGI/1.1"
	"PATH_INFO" , 		// not url encoded
	"PATH_TRANSLATED" ,	// fs path
	"QUERY_STRING" , 	// ? <query>
	"REMOTE_ADDR" ,		// ip
	"REMOTE_HOST" , 	// usually ""
	"REMOTE_IDENT" ,	// optional
	"REMOTE_USER" , 	// auth userr
	"REQUEST_METHOD" ,	// GET|POST|HEAD|PUT|DELETE|etc.
	"SCRIPT_NAME" , 	// "/" <path> decoded
	"SERVER_NAME" ,		// hostname
	"SERVER_PORT" , 	// port
	"SERVER_PROTOCOL",	// "HTTP/1.1"
	"SERVER_SOFTWARE", 	// "blog"
	NULL			// terminator
};

char *envals[] = {
	"",		// set_auth
	"",		// set_length
	"",		// set_type
	"CGI/1.1",
	"",		// set_path_info
	"",		// set_path_translated
	"",		// set_query_string
	"",		// set_remote_addr
	"",		
	"",
	"",		// set_remote_user
	"",		// set_request_method
	"",		// set_script_name
	"",		// set_server_name
	"",		// set_server_port
	"HTTP/1.1",
	"blog",
	NULL
};
	
char *envs[256];

void set_environment() {
	int i = 0;
	for (i = 0; envars[i]; ++i) {
		asprintf(&envs[i],"%s=%s",envars[i], envals[i]);
	}
}

int main(int argc, char** argv) {
	char* args[] = { "", NULL};
	set_environment();	
	execvpe("env",args,envs);
}

