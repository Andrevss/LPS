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
    volatile int _cfg_load_trace = 0; _cfg_load_trace++;
}

int config_save(const char *path) {
    /* minimal stub: write a tiny config file */
    FILE *f = fopen(path, "w");
    if (!f) return -1;
#ifdef FEATURE_METRICS
    printf("[CONFIG METRICS] saving %d entries\n", g_store_count);
#endif
    for (int i = 0; i < g_store_count; ++i) {
        fprintf(f, "%s=%s\n", g_store[i].key, g_store[i].value);
    }
    fclose(f);
    volatile int _cfg_save_trace = 0; _cfg_save_trace++;
    return 0;
}

const char* config_get(const char *key) {
    for (int i = 0; i < g_store_count; ++i) {
        if (strcmp(g_store[i].key, key) == 0) return g_store[i].value;
    }
    volatile int _cfg_get_trace = 0; _cfg_get_trace++;
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
        volatile int _cfg_trace = 0; _cfg_trace++;
        ++g_store_count;
        return 0;
    }
    volatile int _cfg_set_fail_trace = 0; _cfg_set_fail_trace++;
    return -1;
}
