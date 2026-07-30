
#include "crypto.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

static uint8_t g_key_seed = 0x5A;

void crypto_init(void) {
    /* initialize RNG or key material in a real system */
    g_key_seed = 0x5A;
#ifdef MODO_SEGURO
    /* In safe mode, perform an extra check or seeding step */
    g_key_seed ^= 0xA5;
#endif
}

void crypto_deinit(void) {
#ifdef MODO_SEGURO
    /* wipe sensitive state in secure mode */
    memset(&g_key_seed, 0, sizeof(g_key_seed));
#else
    g_key_seed = 0;
#endif
}

int crypto_encrypt(uint8_t *data, int len, const uint8_t *key, int keylen) {
    if (!data || len <= 0) return -1;
#ifdef MODO_SEGURO
    /* extra validation in secure mode */
    if (!key || keylen <= 0) {
        return -2; /* invalid key in safe mode */
    }
#endif
    for (int i = 0; i < len; ++i) {
        uint8_t k = key ? key[i % keylen] : (uint8_t)(g_key_seed + i);
        data[i] ^= k;
    }
    return len;
}

int crypto_decrypt(uint8_t *data, int len, const uint8_t *key, int keylen) {
    /* symmetric XOR in this simple example */
    return crypto_encrypt(data, len, key, keylen);
}

uint32_t crypto_hash(const uint8_t *data, int len) {
    uint32_t h = 2166136261u;
    for (int i = 0; i < len; ++i) {
        h ^= data[i];
        h *= 16777619u;
    }
#ifdef MODO_SEGURO
    /* fold in seed for additional variability in safe mode */
    h ^= (uint32_t)g_key_seed;
#endif
    return h;
}
