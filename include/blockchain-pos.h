#ifndef BLOCKCHAIN_POS_H
#define BLOCKCHAIN_POS_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "../include/digest_sha256.h"

struct block {
    struct block *next;
    char *prev_hash;
    char *hash;
    char *data;
    time_t timestamp;
    char *sender;
    bigint public_key;
    char *signature;
    char *valiator;
    bool valid;
};

typedef struct {
    uint32_t difficulty;
    uint32_t block_count;
    struct block *blocks;
} blockchain_pos;

void construct_empty_blockchain(blockchain_pos *chain, uint32_t difficulty);
void deconstruct_blockchain(blockchain_pos *chain);
void sign_block(blockchain_pos *chain, struct block *block, char *sender);
void add_block(blockchain_pos *chain, char *data);
void blockchain_test(blockchain_pos *chain);
void validate_block(blockchain_pos *chain, uint32_t index);

#endif   // BLOCKCHAIN_POS_H