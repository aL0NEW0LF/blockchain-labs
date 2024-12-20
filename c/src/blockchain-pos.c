#include "../include/blockchain-pos.h"

void construct_empty_blockchain_pos(blockchain_pos *chain) {
    chain->block_count = 1;

    chain->blocks = (struct block *)malloc(sizeof(struct block_pos));
    chain->blocks->next = NULL;
    chain->blocks->prev_hash = NULL;
    chain->blocks->data = "Genesis Block";
    chain->blocks->signature = digest_sha256(chain->blocks->data);
    chain->blocks->timestamp = time(NULL);
}

void add_block_pos(blockchain_pos *chain, char *data, char *sender) {
    struct block_pos *current_block = chain->blocks;

    for (int i = 0; i < chain->block_count - 1; i++) {
        current_block = current_block->next;
    }

    current_block->next = (struct block_pos *)malloc(sizeof(struct block_pos));
    current_block->next->prev_hash = current_block->signature;
    current_block->next->data = data;
    current_block->next->sender = sender;
    current_block->next->public_key = digest_sha256(sender);
    char *to_hash = (char *)malloc(strlen(data) + strlen(current_block->next->public_key) + 1);
    strcpy(to_hash, data);
    strcat(to_hash, current_block->next->public_key);
    current_block->next->signature = digest_sha256(to_hash);
    current_block->next->timestamp = time(NULL);
    current_block->next->next = NULL;
    current_block->next->valiator = NULL;
    chain->block_count++;

    free(to_hash);
    to_hash = NULL;
    current_block = NULL;
}

void deconstruct_blockchain_pos(blockchain_pos *chain) {
    struct block_pos *current_block = chain->blocks;
    struct block_pos *next_block = NULL;

    for (int i = 0; i < chain->block_count; i++) {
        next_block = current_block->next;
        free(current_block);
        current_block = next_block;
    }


    chain = NULL;
    current_block = NULL;
    next_block = NULL;
}

void blockchain_test_pos(blockchain_pos *chain) {
    struct block_pos *current_block = chain->blocks;

    printf("Blockchain Test\n");

    for (int i = 0; i < chain->block_count; i++) {
        printf("Block %d\n", i + 1);
        if (current_block->prev_hash != NULL) {
            printf("Previous Hash: %s\n", current_block->prev_hash);
        } else {
            printf("Previous Hash: None\n");
        }
        printf("Data: %s\n", current_block->data);
        printf("Hash: %s\n", current_block->signature);
        printf("Timestamp: %ld\n", current_block->timestamp);
        printf("Sender: %s\n", current_block->sender);
        printf("Public Key: ");
        if (current_block->public_key != NULL) {
            printf("%s\n", current_block->public_key);
        } else {
            printf("None\n");
        }
        printf("Validator: ");
        if (current_block->valiator != NULL) {
            printf("%s\n", current_block->valiator->username);
        } else {
            printf("None\n");
        }
        printf("\n");

        current_block = current_block->next;
    }

    printf("Blockchain Test Complete\n");
    
    current_block = NULL;
}

struct validator choose_validator(blockchain_pos *chain, struct block_pos *block, struct validator *validators) {
    struct block_pos *current_block = chain->blocks;

    for (int i = 0; i < chain->block_count - 1; i++) {
        current_block = current_block->next;
    }

    uint32_t amount = strtol(current_block->sender, NULL, 10);
    uint32_t max_stake = 0;
    struct validator *max_validator = NULL;
    
    for (int i = 0; i < 3; i++) {
        if (validators[i].stake > max_stake) {
            max_stake = validators[i].stake;
            max_validator = &validators[i];
        }
    }

    return *max_validator;
}

void validate_block_pos(blockchain_pos *chain, uint32_t index, struct validator *validator) {
    struct block_pos *current_block = chain->blocks;

    for (int i = 0; i < index; i++) {
        current_block = current_block->next;
    }

    char *to_hash = (char *)malloc(strlen(current_block->data) + strlen(current_block->public_key) + 1);
    strcpy(to_hash, current_block->data);
    strcat(to_hash, current_block->public_key);
    char *hash = digest_sha256(to_hash);

    if (strcmp(hash, current_block->signature) == 0) {
        current_block->valid = true;
        current_block->valiator = validator;
    } else {
        current_block->valid = false;
        current_block->valiator = validator;
    }

    free(to_hash);
    free(hash);
    hash = NULL;
    to_hash = NULL;
}