// md.h
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

#ifndef __HAVE_MD_H__
#define __HAVE_MD_H__

#include "str.h"
#include "md.h"

int equal(char c);
int dash(char c);
int title(char* s);
int section(char* s);
int paragraph(char* s);
int pre(char* s);
int list(char* s);
int bold(char* s);
int italic(char* s);
int url(char* s);
int image(char * s);
int convert(char* filename);

#endif
