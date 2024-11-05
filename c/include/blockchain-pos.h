#ifndef BLOCKCHAIN_POS_H
#define BLOCKCHAIN_POS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "../include/digest_sha256.h"

struct validator {
    char *username;
    char *public_key;
    uint32_t stake;
};

struct block_pos {
    struct block_pos *next;
    char *prev_hash;
    char *signature;
    char *data;
    time_t timestamp;
    char *sender;
    char *public_key;
    struct validator *valiator;
    bool valid;
};

typedef struct {
    uint32_t block_count;
    struct block_pos *blocks;
} blockchain_pos;

void construct_empty_blockchain_pos(blockchain_pos *chain);
void deconstruct_blockchain_pos(blockchain_pos *chain);
void sign_block_pos(blockchain_pos *chain, struct block_pos *block, char *sender);
void add_block_pos(blockchain_pos *chain, char *data, char *sender);
void blockchain_test_pos(blockchain_pos *chain);
struct validator choose_validator(blockchain_pos *chain, struct block_pos *block, struct validator *validator);
void validate_block_pos(blockchain_pos *chain, uint32_t index, struct validator *validator);

#endif   // BLOCKCHAIN_POS_H