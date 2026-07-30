#include "network.h"
#include <stdio.h>
#include <string.h>

static int g_net_up = 0;
static int g_receive_counter = 0;

#ifdef FEATURE_NETWORK
static int g_net_connected = 0;

static void network_start_service(void) {
    /* start listeners/services */
    g_net_connected = 1;
    printf("network: service started\n");
}

static void network_stop_service(void) {
    g_net_connected = 0;
    printf("network: service stopped\n");
}
#endif

void network_init(void) {
    g_net_up = 1;
#ifdef FEATURE_NETWORK
    network_start_service();
#endif
}

void network_shutdown(void) {
#ifdef FEATURE_NETWORK
    network_stop_service();
#endif
    g_net_up = 0;
}

int network_send(const uint8_t *data, int len) {
    if (!g_net_up) return -1;
#ifdef FEATURE_NETWORK
    if (!g_net_connected) return -2;
    printf("network_send (full): %d bytes\n", len);
#else
    printf("network_send: %d bytes\n", len);
#endif
    return len;
}

int network_receive(uint8_t *buffer, int maxlen) {
    if (!g_net_up) return -1;
    ++g_receive_counter;
#ifdef FEATURE_NETWORK
    /* In full network mode, occasionally return a frame */
    if (g_receive_counter % 3 == 0 && g_net_connected) {
        const char *msg = "FULL_FRAME";
        int mlen = (int)strnlen(msg, maxlen);
        if (mlen > maxlen) mlen = maxlen;
        memcpy(buffer, msg, mlen);
        return mlen;
    }
    return 0;
#else
    if (g_receive_counter % 2 == 0) {
        const char *msg = "ping";
        int mlen = (int)strnlen(msg, maxlen);
        if (mlen > maxlen) mlen = maxlen;
        memcpy(buffer, msg, mlen);
        return mlen;
    }
    return 0; // no data
#endif
}
