/* Firex - Fast and minimalist web framework
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

#ifndef FIREX_FIREX_H
#define FIREX_FIREX_H

#include <inttypes.h>

typedef enum frx_status frx_status_t;
typedef void(*frx_callback_t)(frx_status_t);

enum frx_status {
    FRX_SUCCESS,
    FRX_SOCKERR,
    FRX_SETOPTERR,
    FRX_BINDERR,
    FRX_LISTENERR,
    FRX_CONNERR
};

extern void frx_listen(const char* host, uint16_t port, frx_callback_t callback);

#endif // FIREX_FIREX_H
