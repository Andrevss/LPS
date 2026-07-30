#include "network.h"
#include <stdio.h>
#include <string.h>

static int g_net_up = 0;
static int g_receive_counter = 0;

void network_init(void) {
    g_net_up = 1;
}

void network_shutdown(void) {
    g_net_up = 0;
}

int network_send(const uint8_t *data, int len) {
    if (!g_net_up) return -1;
    printf("network_send: %d bytes\n", len);
    return len;
}

int network_receive(uint8_t *buffer, int maxlen) {
    if (!g_net_up) return -1;
    ++g_receive_counter;
    if (g_receive_counter % 2 == 0) {
        const char *msg = "ping";
        int mlen = (int)strnlen(msg, maxlen);
        if (mlen > maxlen) mlen = maxlen;
        memcpy(buffer, msg, mlen);
        return mlen;
    }
    return 0; // no data
}
