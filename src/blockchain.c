#include "../include/blockchain.h"

void construct_empty_blockchain(blockchain *chain, uint32_t difficulty) {
    chain->difficulty = difficulty;
    chain->block_count = 1;

    chain->blocks = (struct block *)malloc(sizeof(struct block));
    chain->blocks->next = NULL;
    chain->blocks->prev_hash = NULL;
    chain->blocks->data = "Genesis Block";
    chain->blocks->hash = digest_sha256(chain->blocks->data);
    chain->blocks->timestamp = time(NULL);
}

void add_block(blockchain *chain, char *data) {
    struct block *current_block = chain->blocks;

    for (int i = 0; i < chain->block_count - 1; i++) {
        current_block = current_block->next;
    }

    current_block->next = (struct block *)malloc(sizeof(struct block));
    current_block->next->prev_hash = current_block->hash;
    current_block->next->data = data;
    current_block->next->hash = digest_sha256(data);
    current_block->next->timestamp = time(NULL);
    chain->block_count++;
}

void deconstruct_blockchain(blockchain *chain) {
    struct block *current_block = chain->blocks;
    struct block *next_block = NULL;

    for (int i = 0; i < chain->block_count; i++) {
        next_block = current_block->next;
        free(current_block);
        current_block = next_block;
    }
}

void blockchain_test(blockchain *chain) {
    struct block *current_block = chain->blocks;

    printf("Blockchain Test\n");

    for (int i = 0; i < chain->block_count; i++) {
        printf("Block %d\n", i + 1);
        printf("Prev Hash: %s\n", current_block->prev_hash);
        printf("Data: %s\n", current_block->data);
        printf("Hash: %s\n", current_block->hash);
        printf("Timestamp: %ld\n", current_block->timestamp);
        printf("Nonce: %d\n", current_block->nonce);
        printf("\n");

        current_block = current_block->next;
    }

    printf("Blockchain Test Complete\n");
}

void mine_block(blockchain *chain, uint32_t difficulty, uint32_t index) {
    if (index >= chain->block_count || index < 1) {
        printf("Block index out of range\n");
        return;
    }

    struct block *current_block = chain->blocks;

    for (int i = 0; i < index; i++) {
        current_block = current_block->next;
    }

    char *hash = NULL;
    char *prefix = (char *)malloc(difficulty + 1);
    memset(prefix, '0', difficulty);
    prefix[difficulty] = '\0';
    char *nonce = (char *)malloc(11);

    do {
        snprintf(nonce, 11, "%d", current_block->nonce);
        current_block->timestamp = time(NULL);
        hash = get_concat_hash(current_block->data, nonce);
        current_block->nonce++;
    } while (strncmp(hash, prefix, difficulty) != 0);

    current_block->hash = hash;
    free(prefix);
    free(nonce);
}