// test_parse.c
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

// This is the main test progie for the parse

int main(int argc, char** argv) {

	// between
	ok(between('a','z','c'), "c is between a and z");
	fail(between('a','z','C'), "C is not between a and z");

	// num
	ok(num('0'), "0 is a number");
	ok(num('9'), "9 is a number");
	fail(num('/'), "/ is not a number");
	fail(num(':'), "0 is not a number");

	// alpha
	ok(alpha('a'), "a is a letter");	
	ok(alpha('z'), "z is a letter");	
	ok(alpha('A'), "A is a letter");	
	ok(alpha('Z'), "Z is a letter");	
	fail(alpha('@'), "@ is not a letter");	
	fail(alpha('['), "[ is not a letter");	
	fail(alpha('`'), "` is not a letter");	
	fail(alpha('{'), "{ is not a letter");	
	
	// alphanum
	ok(alphanum('a'), "a is alphanum");
	ok(alphanum('z'), "z is alphanum");
	ok(alphanum('A'), "A is alphanum");
	ok(alphanum('Z'), "Z is alphanum");
	ok(alphanum('0'), "0 is alphanum");
	ok(alphanum('9'), "9 is alphanum");
	fail(alpha('@'), "@ is not alphanum ");	
	fail(alpha('['), "[ is not alphanum");	
	fail(alpha('`'), "` is not alphanum");	
	fail(alpha('{'), "{ is not alphanum");	

	// space
	ok(space(' '), "space is space");
	fail(space('\n'), "new line is not space");
	fail(space('\r'), "cr is not space");
	fail(space('\t'), "tab is not space");

	// tab
	ok(tab('\t'), "tab is tab");
	fail(tab(' '), "space is not tab");
	fail(tab('\n'), "new line is not tab");
	fail(tab('\r'), "cr is not tab");
	
	// nl
	ok(nl('\n'), "new line is new line");
	fail(nl('\t'), "tab is not new line");
	fail(nl(' '), "space is not new line");
	fail(nl('\r'), "cr is not new line");
	
	// cr
	fail(cr('\n'), "new line is not cr");
	fail(cr('\t'), "tab is not cr");
	fail(cr(' '), "space is not cr");
	ok(cr('\r'), "cr is cr");
	
	// whitespace
	ok(whitespace('\n'), "new line is whitespace");
	ok(whitespace('\t'), "tab is whitespace");
	ok(whitespace(' '), "space is whitespace");
	ok(whitespace('\r'), "cr is whitespace");
	fail(whitespace('\b'), "backspace is not whitespace");

	// colon
	ok(colon(':'), "colon is colon");
	fail(colon(';'), "semicolon is not colon");

	// semi
	fail(semi(':'), "colon is not semicolon");
	ok(semi(';'), "semicolon is semicolon");

	// slash
	fail(slash('\\'), "\\ is not /");
	ok(slash('/'), "/ is /");

	// dot
	fail(dot('*'), "* is not .");
	ok(dot('.'), ". is .");
	
	// star
	ok(star('*'), "* is *");
	fail(star('.'), ". is not *");
	
	// question
	ok(question('?'), "? is ?");

	// hex
	ok(hex('a'), "a is hex");
	ok(hex('f'), "f is hex");
	ok(hex('A'), "A is hex");
	ok(hex('F'), "F is hex");
	ok(hex('0'), "0 is hex");
	ok(hex('9'), "9 is hex");
	fail(hex('g'), "g is not hex");
	fail(hex('G'), "G is not hex");
	
	// decimal
	ok(decimal('0'), "0 is decimal");
	ok(decimal('9'), "9 is decimal");
	ok(decimal('.'), ". is decimal");
	fail(decimal('a'), "a is not decimal");

	// ctrl
	ok(ctrl('\b'), "Backspace is ctrl");
	ok(ctrl('\a'), "Bell is ctrl");
	ok(ctrl(127), "Del is ctrl");
	fail(ctrl('a'), "a is not ctrl");

	// any 
	value(3,any(alpha,"abc123"), "three letters at abc123");
	value(0,any(num,"abc123"), "no numbers at abc123");
	value(6,any(alphanum,"abc123"), "six alphanum in abc123");
	
	// until
	value(5,until(space,"hello world!"), "5 letters until space");
	value(11,until(question,"hello world?"), "11 letters until question");
	value(12,until(ctrl,"hello world?"), "12 chacters till end");

	// crlf, eol, and upto
	value(6, upto(eol, "line 1\r\nline 1\r\n"), "6 chars upto crlf");
	value(0, upto(eol, "\r\n\r\n"), "0 characters to end of line");
	value(12, upto(eol, "hello world!"), "12 characters to eol");

	// all test
	value(5, all(dot, ".....\r\n"), "there are 5 dots");

	return done("test_parse");
}
