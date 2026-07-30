#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char key[32];
    char value[64];
} kv_t;

static kv_t g_store[8];
static int g_store_count = 0;

void config_load(const char *path) {
    /* minimal stub: pretend to load one value */
    (void)path;
    g_store_count = 1;
    strncpy(g_store[0].key, "mode", sizeof(g_store[0].key)-1);
    strncpy(g_store[0].value, "normal", sizeof(g_store[0].value)-1);
}

int config_save(const char *path) {
    /* minimal stub: write a tiny config file */
    FILE *f = fopen(path, "w");
    if (!f) return -1;
    for (int i = 0; i < g_store_count; ++i) {
        fprintf(f, "%s=%s\n", g_store[i].key, g_store[i].value);
    }
    fclose(f);
    return 0;
}

const char* config_get(const char *key) {
    for (int i = 0; i < g_store_count; ++i) {
        if (strcmp(g_store[i].key, key) == 0) return g_store[i].value;
    }
    return NULL;
}

int config_set(const char *key, const char *value) {
    for (int i = 0; i < g_store_count; ++i) {
        if (strcmp(g_store[i].key, key) == 0) {
            strncpy(g_store[i].value, value, sizeof(g_store[i].value)-1);
            return 0;
        }
    }
    if (g_store_count < (int)(sizeof(g_store)/sizeof(g_store[0]))) {
        strncpy(g_store[g_store_count].key, key, sizeof(g_store[g_store_count].key)-1);
        strncpy(g_store[g_store_count].value, value, sizeof(g_store[g_store_count].value)-1);
        ++g_store_count;
        return 0;
    }
    return -1;
}
