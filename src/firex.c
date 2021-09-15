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

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "firex.h"

#define DEFAULT_RESPONSE \
    "HTTP/1.1 200 OK\r\n" \
    "Content-Type: text/html; charset=utf-8\r\n" \
    "\r\n" \
    "<h1>Hello World!</h1>"

static void handle(int connection) {
    char buffer[30000] = { 0 };
    read(connection, buffer, 30000);
    printf("%s\n", buffer);

    sleep(5);

    char* message = DEFAULT_RESPONSE;
    write(connection, message, strlen(message));
}

extern void frx_listen(const char* host, uint16_t port, frx_callback_t callback) {
    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = { .s_addr = inet_addr(host) }
    };

    int listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0) {
        return callback(FRX_SOCKERR);
    }
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0) {
        return callback(FRX_SETOPTERR);
    }
    if (bind(listener, (struct sockaddr*)&address, sizeof(address)) != 0) {
        return callback(FRX_BINDERR);
    }
    if (listen(listener, SOMAXCONN) != 0) {
        return callback(FRX_LISTENERR);
    }

    callback(FRX_SUCCESS);
    while (1) {
        int connection = accept(listener, NULL, NULL);
        if (connection < 0) {
            return callback(FRX_CONNERR);
        }

        handle(connection);
        close(connection);
    }
}
