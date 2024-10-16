#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include "../include/digest_sha256.h"

struct block {
    struct block *next;
    char *prev_hash;
    char *hash;
    char *data;
    time_t timestamp;
    uint32_t nonce;
};

typedef struct {
    uint32_t difficulty;
    uint32_t block_count;
    struct block *blocks;
} blockchain;

void construct_empty_blockchain(blockchain *chain, uint32_t difficulty);
void deconstruct_blockchain(blockchain *chain);
void add_block(blockchain *chain, char *data);
void blockchain_test(blockchain *chain);
void mine_block(blockchain *chain, uint32_t difficulty, uint32_t index);

#endif   // BLOCKCHAIN_H