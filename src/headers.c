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

#include <malloc.h>

#include "firex/headers.h"

extern frx_headers_t* frx_headers_new(char* name, char* value) {
    frx_headers_t* node = (frx_headers_t*) malloc(sizeof(frx_headers_t));
    node->name = name;
    node->value = value;
    node->next = NULL;
    return node;
}

extern void frx_headers_free(frx_headers_t* headers) {
    while (headers != NULL) {
        frx_headers_t* next = headers->next;

        free(headers->name);
        free(headers->value);
        free(headers);

        headers = next;
    }
}
