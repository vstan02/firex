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

#include <malloc.h>
#include <string.h>
#include <ctype.h>

#include "firex/request.h"

static char* str_read(char*, const char*, size_t);

extern void frx_request_init(frx_request_t* request, char* source) {
    request->method = str_read(source, " ", 0);
    request->url = str_read(NULL, " ", 0);
    request->version = str_read(NULL, " \n\r", 5);

    request->headers = NULL;
    char* name = str_read(NULL, ":", 0);
    char* value = str_read(NULL, "\n\r", 0);
    while (name != NULL && value != NULL) {
        frx_headers_t* node = frx_headers_new(name, value);
        node->next = request->headers;
        request->headers = node;

        name = str_read(NULL, ":", 0);
        value = str_read(NULL, "\n\r", 0);
    }
}

extern void frx_request_free(frx_request_t* request) {
    free(request->url);
    free(request->method);
    free(request->version);
    frx_headers_free(request->headers);
}

static char* str_read(char* source, const char* delim, size_t ignore) {
    static char* str = NULL;

    if (source != NULL) str = source;
    if (*str == '\0') return NULL;

    while (isspace(*str)) ++str;
    str += ignore;
    size_t size = strcspn(str, delim);
    str[size] = '\0';

    char* result = strdup(str);
    str += size + 1;
    return result;
}
