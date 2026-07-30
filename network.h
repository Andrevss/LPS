#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>

void network_init(void);
void network_shutdown(void);
int network_send(const uint8_t *data, int len);
int network_receive(uint8_t *buffer, int maxlen);

#endif // NETWORK_H
