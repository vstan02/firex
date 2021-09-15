#include <stdio.h>
#include <firex.h>

#define HOST "127.0.0.1"
#define PORT 3000

static void on_listen(frx_status_t status) {
    switch (status) {
        case FRX_SUCCESS:
            printf(">>> http://%s:%i\n", HOST, PORT); break;
        case FRX_SOCKERR:
            fprintf(stderr, "Cannot create socket\n"); break;
        case FRX_SETOPTERR:
            fprintf(stderr, "Cannot set socket option\n"); break;
        case FRX_BINDERR:
            fprintf(stderr, "Cannot bind address to the socket\n"); break;
        case FRX_LISTENERR:
            fprintf(stderr, "Cannot listen to the socket\n"); break;
        case FRX_CONNERR:
            fprintf(stderr, "Cannot accept connection\n"); break;
    }
}

int main(void) {
    frx_listen(HOST, PORT, on_listen);
    return 0;
}
