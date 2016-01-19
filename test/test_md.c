// test_md.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "parse.h"
#include "md.h"

// This is the main test progie for the md

int main(int argc, char** argv) {

	// equal tests
	ok(equal('='), "= is =");
	fail(equal('-'), "- is not =");

	// dash tests
	ok(dash('-'), "- is -");
	fail(dash('='), "= is not -");

	// title tests
	value(0,title("this is a test"), "not a title");
	value(0,title("this is a test\nof not a title"), "not a title with two lines");
	value(0,title("abcde\r\n-----\r\n"), "a 5 character section");
	value(14,title("abcde\r\n=====\r\n"), "a 5 character title");

	// section tests
	value(0,section("this is a test"), "not a title");
	value(0,section("this is a test\nof not a title"), "not a title with two lines");
	value(14,section("abcde\r\n-----\r\n"), "a 5 character section");
	value(0,section("abcde\r\n=====\r\n"), "a 5 character title");

	// paragraph tests
	value(0,paragraph(""), "empty string");
	value(0,paragraph("\n\n"), "blank line n n");
	value(0,paragraph("\r\n\r\n"), "blank line rn rn");
	value(0,paragraph("\n\r\n"), "blank line n rn");
	value(0,paragraph("\n\r\n"), "blank line n rn");
	value(7,paragraph("abc\ndef"), "line with break");
	value(7,paragraph("abc\ndef\n\nghi"), "2 lines with follow on paragraph");

	// pre tests
	value(0,pre("abc\r\n"),"not pre");
	value(5,pre("\tabc\n"), "pre");
	value(15,pre("\tabc\n\tdef\n\tghi\nfoobar\n"), "3 lines of pre");

	// list
	value(0,list("abc\r\n"), "not a list");
	value(5,list("* abc\r\n"), "abc list");
	value(5,list("* abc\r\n* def\n"), "abc list with following list");

	// bold
	value(0,bold("abc\n"), "not bold");
	value(0,bold("abc*\n"), "also not bold");
	value(5,bold("*abc*\n"), "bold");
	value(5,bold("*a\nc*\n"), "bold across two lines");
	value(4,bold("*abc"), "short bold");

	// italics
	value(0,italic("abc\n"), "not italic");
	value(0,italic("abc/\n"), "also not italic");
	value(5,italic("/abc/\n"), "italic");
	value(5,italic("/a\nc/\n"), "italic across two lines");
	value(4,italic("/abc"), "italic short");

	// url
	value(0,url("abc"), "not a url");
	value(5,url("[abc]"), "a url");
	value(4,url("[abc"), "a url without end");
	
	// image
	value(0,image("abc"), "not a image");
	value(5,image("{abc}"), "a image");
	value(4,image("{abc"), "a image without end");

	return done("test_parse");
}
