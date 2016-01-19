// html.h
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

#ifndef __HAVE_HTML_H__
#define __HAVE_HTML_H__

void h1(str* s);
void h2(str* s);
void h3(str* s);
void h4(str* s);
void h5(str* s);
void p(str* s);
void pre(str* s);
void li(str* s);
void bld(str* s);
void itc(str* s);
void href(str* u, str* l);
void img(str* u, str* l);

#endif
