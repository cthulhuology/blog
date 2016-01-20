// md.c
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
#include "parse.h"
#include "md.h"
#include "html.h"

// equal
//
// 	returns true if the character is an equals sign
//
int equal(char c) {
	return c == '=';
}

// dash
//
// 	returns true if the character is a dash
//
int dash(char c) {
	return c == '-';
}

// title
//
// 	parses a title which is a line followed by
// 	==========================================
//
int title(char* s) {
	int i,n,t;
	t = upto(eol,s);	// grab the potential title
	n = eol(s+t) + t;
	i = all(equal,s+n);
	if (i == 0) return 0;
	return n + i + eol(s+i+n);
}

// section
//
// 	parses a section which is a line followed by
// 	--------------------------------------------
//
int section(char* s) {
	int i,n,t;
	t = upto(eol,s);	// grab the potential title
	n = eol(s+t) + t;
	i = all(dash,s+n);
	if (i == 0) return 0;
	return n + i + eol(s+i+n);
}

// blank
//
//	returns length line if found
//
int blank(char* s) {
	int i,j;
	i = eol(s);
	if (!i) return 0;
	j = eol(s+i);
	if (!j) return 0;
	return i+j;	
}

// paragraph
//
// 	parses a paragraph which is text followed by
// 	a blank line.
//
int paragraph(char* s) {
	return upto(blank,s);
}

// preformat
//
// 	parses preformatted text which is a paragraph
// 	that starts with whitespace on each line
//
int preformat(char* s) {
	int i = 0;
	while( whitespace(s[i]) ) {	// start of line is whitespace
		i += upto(eol,s+i);	// go to end of line
		i += eol(s+i);		// advance to next line
	}
	return i;			// return total length of all lines
}

// list
// 
// 	parses a list of items which all start with a *
//
int list(char* s) {
	int i = 0;
	if (star(s[0]) && whitespace(s[1])) i = upto(eol,s);
	return i;
}

// bold
//
// 	converts a set of words surrounded by * * to bold
// 	this includes the starting * and trailing *
//
int bold(char* s) {
	int i = 0;
	if (star(s[0]) && !whitespace(s[1])) i = 1 + until(star,s+1);
	if (i > 0) i += star(s[i]);;	// +1 if trailling star
	return i;			
}

// italics
//
// 	converts a set of words surrounded by / / to italic
//
int italic(char* s) {
	int i = 0;
	if (slash(s[0]) && !whitespace(s[1])) i = 1 + until(slash,s+1);
	if (i > 0) i += slash(s[i]); // +1 if trailing /
	return i;
}

// url
//
// 	converts [ HREF | Label ]  or [ HREF ]to a <a href=
//
int url(char* s) {
	int i = 0;
	if (lbracket(s[0])) i = until(rbracket,s);
	if (i > 0) i += rbracket(s[i]);
	return i;
}

// image
//
// 	converts a { IMG | Label } or { IMG } to an <img src=
//
int image(char* s) {
	int i = 0;
	if (lsquigle(s[0])) i = until(rsquigle,s);
	if (i > 0) i += rsquigle(s[i]);
	return i;
}



// render
//
// 	render an .md file, and attempts  
//
int render(str* doc) {
	int i = 0, t, l;
	char* s = doc->data;
	while (i < doc->length) {
		if (t = title(s+i)) { 		// we have a title
			l = upto(eol,s+i);
			h1(ref(s+i,l));
			i += t;
			i += any(whitespace,s+i);
			continue;
		}
		if (t = section(s+i)) {		// we have a section
			l = upto(eol,s+i);
			h2(ref(s+i,l));
			i += t;
			i += any(whitespace,s+i);
			continue;
		}
		if (t = paragraph(s+i)) {
			p(ref(s+i,t));
			i += t;
			i += any(whitespace,s+i);
			continue;
		}
		++i;
	}
}



#ifndef TEST

// main

int main (int argc, char** argv) {
	str* s = in();
	render(s);
}

#endif
