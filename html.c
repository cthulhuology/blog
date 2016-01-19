// html.c
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

// h1
//
// 	render a h1 tag
//
void h1(str* s) {
	outs("<h1>",4);
	out(s);
	outs("</h1>\n",6);
}

// h2
//
// 	render a h2 tag
//
void h2(str* s) {
	outs("<h2>",4);
	out(s);
	outs("</h2>\n",6);
}

// h3
//
// 	render a h3 tag
//
void h3(str* s) {
	outs("<h3>",4);
	out(s);
	outs("</h3>\n",6);
}

// h4
//
// 	render a h4 tag
//
void h4(str* s) {
	outs("<h4>",4);
	out(s);
	outs("</h4>\n",6);
}

// h5
//
// 	render a h5 tag
//
void h5(str* s) {
	outs("<h5>",4);
	out(s);
	outs("</h5>\n",6);
}

// p
//
// 	render a p tag
//
void p(str* s) {
	outs("<p>",3);
	out(s);
	outs("</p>\n",5);
}

// pre
//
// 	render a pre tag
//
void pre(str* s) {
	outs("<pre>",5);
	out(s);
	outs("</pre>\n",7);
}

// li
//
// 	renders a li tag
//
void li(str* s) {
	outs("<li>",4);
	out(s);
	outs("</li>\n",6);
}

// bld
//
// 	renders a b tag
//
void bld(str* s) {
	outs("<b>",3);
	out(s);	
	outs("</b>",4);
}

// itc
//
// 	renders a i tag
//
void itc(str* s) {
	outs("<i>",3);
	out(s);
	outs("</i>",4);
}

// href
//
// 	renders a <a href tag
// 	takes a url u 
// 	and an optional label l
//
void href(str* u, str* l) {
	outs("<a href=\"",9);
	out(u);
	outs("\">",2);
	out( l ? l : u );
	outs("</a>",4);
}

// img
//
// 	renders an image
// 	takes a url u
// 	and an optional label l
//
void img(str* u, str* l) {
	outs("<img src=\"",10);
	out(u);
	outs("\" alt=\"",7);
	out( l ? l : u );
	outs("\" />",4);
}

