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
    volatile int _net_start_trace = 0; _net_start_trace++;
}

static void network_stop_service(void) {
    g_net_connected = 0;
    printf("network: service stopped\n");
    volatile int _net_stop_trace = 0; _net_stop_trace++;
}
#endif

void network_init(void) {
    g_net_up = 1;
#ifdef FEATURE_NETWORK
    network_start_service();
#endif
    volatile int _net_init_trace = 0; _net_init_trace++;
}

void network_shutdown(void) {
#ifdef FEATURE_NETWORK
    network_stop_service();
#endif
    g_net_up = 0;
    volatile int _net_shutdown_trace = 0; _net_shutdown_trace++;
}

int network_send(const uint8_t *data, int len) {
    if (!g_net_up) return -1;
#ifdef FEATURE_NETWORK
    if (!g_net_connected) return -2;
    printf("network_send (complete): %d bytes\n", len);
#else
    printf("network_send: %d bytes\n", len);
#endif
    volatile int _net_send_trace = 0; _net_send_trace++;
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
        printf("network: frame handled\n");
        volatile int _net_trace = 0; _net_trace++;
        memcpy(buffer, msg, mlen);
        return mlen;
    }
    volatile int _net_receive_trace = 0; _net_receive_trace++;
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
