#include <stdio.h>
#include <firex/firex.h>

#define HOST "127.0.0.1"
#define PORT 3000

static void on_listen(void) {
    printf(">>> http://%s:%i\n\n", HOST, PORT);
}

int main(void) {
    frx_status_t status = frx_listen(HOST, PORT, on_listen);
    if (status != FRX_SUCCESS) {
        fprintf(stderr, "An error occurred");
        return 1;
    }
    return 0;
}
