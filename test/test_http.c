// test_http.c
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

#include "test.h"
#include "parse.h"
#include "http.h"

// this is the main test progie for the http service

int main(int argc, char** argv) {

	// separator
	ok(separator('('), "( is a separator");
	ok(separator('<'), "< is a separator");
	ok(separator('>'), "> is a separator");
	ok(separator('@'), "@ is a separator");
	ok(separator(','), ", is a separator");
	ok(separator(';'), "; is a separator");
	ok(separator(':'), ": is a separator");
	ok(separator('\\'), "\\ is a separator");
	ok(separator('"'), "\" is a separator");
	ok(separator('/'), "/ is a separator");
	ok(separator('['), "[ is a separator");
	ok(separator(']'), "] is a separator");
	ok(separator('?'), "? is a separator");
	ok(separator('='), "= is a separator");
	ok(separator('{'), "{ is a separator");
	ok(separator('}'), "} is a separator");
	ok(separator(' '), "space is a separator");
	ok(separator('\t'), "tab is a separator");
	fail(separator('\n'), "nl is not a separator");
	fail(separator('\r'), "cr is not a separator");
	fail(separator('a'), "a is not a separator");
	fail(separator('z'), "z is not a separator");
	fail(separator('A'), "A is not a separator");
	fail(separator('Z'), "Z is not a separator");
	fail(separator('0'), "0 is not a separator");
	fail(separator('9'), "9 is not a separator");
	fail(separator('-'), "- is not a separator");
	fail(separator('_'), "_ is not a separator");

	// terminators for tokens
	ok(terminator('('), "( is a terminator");
	ok(terminator('<'), "< is a terminator");
	ok(terminator('>'), "> is a terminator");
	ok(terminator('@'), "@ is a terminator");
	ok(terminator(','), ", is a terminator");
	ok(terminator(';'), "; is a terminator");
	ok(terminator(':'), ": is a terminator");
	ok(terminator('\\'), "\\ is a terminator");
	ok(terminator('"'), "\" is a terminator");
	ok(terminator('/'), "/ is a terminator");
	ok(terminator('['), "[ is a terminator");
	ok(terminator(']'), "] is a terminator");
	ok(terminator('?'), "? is a terminator");
	ok(terminator('='), "= is a terminator");
	ok(terminator('{'), "{ is a terminator");
	ok(terminator('}'), "} is a terminator");
	ok(terminator(' '), "space is a terminator");
	ok(terminator('\t'), "tab is a terminator");
	ok(terminator('\n'), "nl is a terminator");
	ok(terminator('\r'), "cr is a terminator");
	fail(terminator('a'), "a is not a terminator");
	fail(terminator('z'), "z is not a terminator");
	fail(terminator('A'), "A is not a terminator");
	fail(terminator('Z'), "Z is not a terminator");
	fail(terminator('0'), "0 is not a terminator");
	fail(terminator('9'), "9 is not a terminator");
	fail(terminator('-'), "- is not a terminator");
	fail(terminator('_'), "_ is not a terminator");

	// token
	value(14,token("Content-Length: 123"),"Content-Length token");
	value(6,token("abc123\r\nefg456"),"abc123 token");
	value(4,token("HTTP/1.1"),"HTTP/1.1 version token");
	value(0,token(" HTTP/1.1"),"space  HTTP/1.1 version token");

	// method
	value(3,method("GET / HTTP/1.1"), "GET method");
	value(4,method("POST / HTTP/1.1"), "POST method");
	value(7,method("OPTIONS / HTTP/1.1"), "OPTIONS method");
	value(11,method("hello-world / HTTP/1.1"), "hello-world method");

	// path
	value(1, path(&("GET / HTTP/1.1")[4]), "/ path");
	value(4, path(&("GET /foo HTTP/1.1")[4]), "/foo path");
	value(1, path(&("GET * HTTP/1.1")[4]), "* path");
	
	// version
	value(8, version(&("GET / HTTP/1.1")[6]), "HTTP/1.1 version");
	value(9, version(&("GET / HTTP/2.11")[6]), "HTTP/2.11 version");

	// request_line
	value(22,request_line("hello-world / HTTP/1.1\r\n"), "request_line with extension methodd");
	value(11,request.method->length, "request.method->length");
	value(0,strncmp(request.method->data,"hello-world",11), "method content");
	value(1,request.path->length, "request.path->length");
	value(0,strncmp(request.path->data,"/",1), "path content");
	value(8,request.version->length, "request.version->length");
	value(0,strncmp(request.version->data,"HTTP/1.1",8), "version content");
	value(26,request_line("  hello-world  /  HTTP/1.1\r\n"), "request_line with invalid padding");

	// header
	value(25,header("  User-Agent: curl/7.38.0\r\n"),"User-Agent header with buggy spacing");
	value(20,header("Host: 127.0.0.1:8080\r\n"),"Host header");
	value(11,header("Accept: */*\n"),"Accept header");
	value(6,header("\t,gzip\r\n"),"extended Accept header");
	value(9,request.header[5]->length, "updated accept header length");
	value(10,header("Ignore: me\r\n"), "ignore a header past max");
	value(3,request.headers, "verify max_headers cf. -DMAX_HEADERS=3 in Makefile");

	return done("test_http");
}
