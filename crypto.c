#include "crypto.h"
#include <stdint.h>
#include <stddef.h>

static uint8_t g_key_seed = 0x5A;

void crypto_init(void) {
    /* initialize RNG or key material in a real system */
    g_key_seed = 0x5A;
}

void crypto_deinit(void) {
    g_key_seed = 0;
}

int crypto_encrypt(uint8_t *data, int len, const uint8_t *key, int keylen) {
    if (!data || len <= 0) return -1;
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
    return h;
}
