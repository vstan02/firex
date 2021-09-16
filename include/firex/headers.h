/* Headers - Collection of HTTP headers
 * Copyright (C) 2021 Stan Vlad <vstan02@protonmail.com>
 *
 * This file is part of Firex.
 *
 * Firex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef FIREX_HEADERS_H
#define FIREX_HEADERS_H

typedef struct frx_headers frx_headers_t;

struct frx_headers {
    char* name;
    char* value;
    frx_headers_t* next;
};

extern frx_headers_t* frx_headers_new(char* name, char* value);
extern void frx_headers_free(frx_headers_t* headers);

#endif // FIREX_HEADERS_H
