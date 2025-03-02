#include <stdio.h>
#include <stdlib.h>
#include "cache_lru.h"

#define CACHE_SIZE 10

typedef struct CacheNode {
    int rod_length;
    int total_value;
    struct CacheNode* next;
} CacheNode;

CacheNode* cache_head = NULL;

void move_front(CacheNode* node) {
    if (cache_head == node) return;

    CacheNode *prev = NULL, *temp = cache_head;
    while (temp && temp != node) {
        prev = temp;
        temp = temp->next;
    }

    if (prev && temp) {
        prev->next = temp->next;
        temp->next = cache_head;
        cache_head = temp;
    }
}

int lookup_cache(int rod_length) {
    CacheNode* temp = cache_head;
    while (temp) {
        if (temp->rod_length == rod_length) {
            move_front(temp);
            return temp->total_value;
        }
        temp = temp->next;
    }
    return -1;
}

void insert_cache(int rod_length, int total_value) {
    if (lookup_cache(rod_length) != -1) return;

    CacheNode* new_node = (CacheNode*)malloc(sizeof(CacheNode));
    new_node->rod_length = rod_length;
    new_node->total_value = total_value;
    new_node->next = cache_head;
    cache_head = new_node;
}