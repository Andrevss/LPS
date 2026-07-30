#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdint.h>

void crypto_init(void);
void crypto_deinit(void);
int crypto_encrypt(uint8_t *data, int len, const uint8_t *key, int keylen);
int crypto_decrypt(uint8_t *data, int len, const uint8_t *key, int keylen);
uint32_t crypto_hash(const uint8_t *data, int len);

#endif // CRYPTO_H
