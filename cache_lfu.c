#include <stdio.h>
#include <stdlib.h>
#include "cache_lfu.h"

#define CACHE_SIZE 10

typedef struct {
    int rod_length;
    int total_value;
    int frequency;
} CacheEntry;

CacheEntry cache[CACHE_SIZE];
int cache_count = 0;

int lfu_find_index() {
    int min_freq = cache[0].frequency, index = 0;
    for (int i = 1; i < cache_count; i++) {
        if (cache[i].frequency < min_freq) {
            min_freq = cache[i].frequency;
            index = i;
        }
    }
    return index;
}

int lookup_cache(int rod_length) {
    for (int i = 0; i < cache_count; i++) {
        if (cache[i].rod_length == rod_length) {
            cache[i].frequency++;
            return cache[i].total_value;
        }
    }
    return -1;
}

void insert_cache(int rod_length, int total_value) {
    if (cache_count < CACHE_SIZE) {
        cache[cache_count].rod_length = rod_length;
        cache[cache_count].total_value = total_value;
        cache[cache_count].frequency = 1;
        cache_count++;
    } else {
        int index = lfu_find_index();
        cache[index].rod_length = rod_length;
        cache[index].total_value = total_value;
        cache[index].frequency = 1;
    }
}