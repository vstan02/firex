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

#include "firex/firex.h"
#include "firex/request.h"

#define DEFAULT_RESPONSE \
    "HTTP/1.1 200 OK\r\n" \
    "Content-Type: text/html; charset=utf-8\r\n" \
    "\r\n" \
    "<h1>Hello World!</h1>"

#define ERROR_RESPONSE \
    "HTTP/1.1 404 Not found\r\n" \
    "Content-Type: text/html; charset=utf-8\r\n" \
    "\r\n" \
    "<h1>Error 404: Page not found!</h1>"

static void handle(int connection) {
    char buffer[BUFSIZ] = { 0 };
    read(connection, buffer, BUFSIZ);

    frx_request_t request;
    frx_request_init(&request, buffer);

    printf("--- Request ---\n");
    printf("> version: %s\n", request.version);
    printf("> url: %s\n", request.url);
    printf("> method: %s\n", request.method);

    printf("> headers:\n");
    frx_headers_t* node = request.headers;
    while (node != NULL) {
        printf("--| %s: %s\n", node->name, node->value);
        node = node->next;
    }
    printf("\n\n");

    char* message = strcmp(request.url, "/") ? ERROR_RESPONSE : DEFAULT_RESPONSE;
    write(connection, message, strlen(message));

    frx_request_free(&request);
}

extern frx_status_t frx_listen(const char* host, uint16_t port, frx_callback_t callback) {
    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = { .s_addr = inet_addr(host) }
    };

    int listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0) {
        return FRX_SOCKERR;
    }
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &(int) { 1 }, sizeof(int)) < 0) {
        return FRX_SETOPTERR;
    }
    if (bind(listener, (struct sockaddr*) &address, sizeof(address)) != 0) {
        return FRX_BINDERR;
    }
    if (listen(listener, SOMAXCONN) != 0) {
        return FRX_LISTENERR;
    }

    if (callback != NULL) {
        callback();
    }

    while (1) {
        int connection = accept(listener, NULL, NULL);
        if (connection < 0) {
            return FRX_CONNERR;
        }

        handle(connection);
        close(connection);
    }
}
