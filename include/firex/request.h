/* Request - HTTP Request
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

#ifndef FIREX_REQUEST_H
#define FIREX_REQUEST_H

#include "headers.h"

typedef struct frx_request frx_request_t;

struct frx_request {
    char* url;
    char* method;
    char* version;
    frx_headers_t* headers;
};

extern void frx_request_init(frx_request_t* request, char* source);
extern void frx_request_free(frx_request_t* request);

#endif // FIREX_REQUEST_H
