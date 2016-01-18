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
#include "md.h"

// title
//
// 	parses a title which is a line followed by
// 	==========================================
//
int title(char* s) {
	
}

// section
//
// 	parses a section which is a line followed by
// 	--------------------------------------------
//
int section(char* s) {

}

// paragraph
//
// 	parses a paragraph which is text followed by
// 	a blank line.
//
int paragraph(char* s) {

}

// pre
//
// 	parses preformatted text which is a paragraph
// 	that starts with whitespace on each line
//
int pre(char* s) {

}

// list
// 
// 	parses a list of items which all start with a *
//
int list(char* s) {

}

// bold
//
// 	converts a set of words surrounded by * * to bold
//
int bold(char* s) {

}

// italics
//
// 	converts a set of words surrounded by / / to italic
//
int italic(char* s) {

}

// link
//
// 	converts [ HREF | Label ]  or [ HREF ]to a <a href=
//
int link(char* s) {

}

// image
//
// 	converts a { IMG | Label } or { IMG } to an <img src=
//
int image(char * s) {

}


