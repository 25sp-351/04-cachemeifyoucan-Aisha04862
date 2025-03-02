#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache_lfu.h"
#include "cache_lru.h"

typedef struct {
    int length;
    int value;
} RodPiece;

#define MAX_PIECES 100

RodPiece pieces[MAX_PIECES];
int piece_count = 0;

//Read input from a file
void read_input() {
    int length, value;
    while (scanf("%d, %d", &length, &value) == 2) {
        pieces[piece_count].length = length;
        pieces[piece_count].value = value;
        piece_count++;
    }
}

//use dp programming 
int rod_cutting(int rod_length) {
    int dp[rod_length + 1];
    int cuts[rod_length + 1];

    
    for (int i = 0; i <= rod_length; i++) {
        dp[i] = 0;
        cuts[i] = -1;
    }

    
    int cached_value = lookup_cache(rod_length);
    if (cached_value != -1) {
        return cached_value;
    }

    // Solve rod cut using DP
    for (int i = 1; i <= rod_length; i++) {
        for (int j = 0; j < piece_count; j++) {
            if (pieces[j].length <= i) {
                int new_val = dp[i - pieces[j].length] + pieces[j].value;
                if (new_val > dp[i]) {
                    dp[i] = new_val;
                    cuts[i] = j;
                }
            }
        }
    }

    // Print distribution of cuts
    int remaining_length = rod_length;
    while (remaining_length > 0 && cuts[remaining_length] != -1) {
        int piece_idx = cuts[remaining_length];
        printf("1 @ %d = %d\n", pieces[piece_idx].length, pieces[piece_idx].value);
        remaining_length -= pieces[piece_idx].length;
    }

    printf("Remainder: %d\n", remaining_length);
    printf("Total Value: %d\n", dp[rod_length]);

    // Store the result in a cache
    insert_cache(rod_length, dp[rod_length]);

    return dp[rod_length];
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <rod_length> < input.txt>\n", argv[0]);
        return 1;
    }

    int rod_length = atoi(argv[1]);
    read_input(); 
     
    // Calculate optimal cuts for the given rod length
    rod_cutting(rod_length);  

    return 0;
}