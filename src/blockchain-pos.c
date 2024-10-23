#include "../include/blockchain-pos.h"
#include "../include/rsa.h"

void construct_empty_blockchain(blockchain_pos *chain, uint32_t difficulty) {
    chain->difficulty = difficulty;
    chain->block_count = 1;

    chain->blocks = (struct block *)malloc(sizeof(struct block));
    chain->blocks->next = NULL;
    chain->blocks->prev_hash = NULL;
    chain->blocks->data = "Genesis Block";
    chain->blocks->hash = digest_sha256(chain->blocks->data);
    chain->blocks->timestamp = time(NULL);
}

void sign_block(blockchain_pos *chain, struct block *block, char *sender) {
    block->sender = sender;
    bigint p1 = bigint_from_string(block->hash);
    bigint p2 = bigint_from_string(block->data);

    bigint n = bigint_mul(p1, p2);
    bigint t = totient(p1, p2);

    bigint e = bigint_from_string("65537");
    if (!bigint_lt(e, t))
        e = bigint_from_int(17);
    if (!bigint_lt(e, t))
        e = bigint_from_int(5);
    if (!bigint_lt(e, t))
        e = bigint_from_int(3);
    if (!bigint_lt(e, t))
        e = bigint_from_int(2);

    block->public_key = e;

    bigint d = bigint_modinv(e, t);

    block->signature = encrypt_text(block->data, e, n);

    bigint_delete(p1);
    bigint_delete(p2);
    bigint_delete(n);
    bigint_delete(t);
    bigint_delete(e);
    bigint_delete(d);
}


void add_block(blockchain_pos *chain, char *data, char *sender) {
    struct block *current_block = chain->blocks;

    for (int i = 0; i < chain->block_count - 1; i++) {
        current_block = current_block->next;
    }

    current_block->next = (struct block *)malloc(sizeof(struct block));
    current_block->next->prev_hash = current_block->hash;
    current_block->next->data = data;
    current_block->next->hash = digest_sha256(data);
    current_block->next->timestamp = time(NULL);
    current_block->next->next = NULL;
    current_block->next->sender = sender;
    sign_block(chain, current_block->next, sender);
    current_block->next->valiator = NULL;
    chain->block_count++;
}

void deconstruct_blockchain(blockchain_pos *chain) {
    struct block *current_block = chain->blocks;
    struct block *next_block = NULL;

    for (int i = 0; i < chain->block_count; i++) {
        next_block = current_block->next;
        free(current_block);
        current_block = next_block;
    }
}

void blockchain_test(blockchain_pos *chain) {
    struct block *current_block = chain->blocks;

    printf("Blockchain Test\n");

    for (int i = 0; i < chain->block_count; i++) {
        printf("Block %d\n", i + 1);
        printf("Prev Hash: %s\n", current_block->prev_hash);
        printf("Data: %s\n", current_block->data);
        printf("Hash: %s\n", current_block->hash);
        printf("Timestamp: %ld\n", current_block->timestamp);
        printf("Sender: %s\n", current_block->sender);
        printf("Public Key: ");
        bigint_print(current_block->public_key);
        printf("\n");

        current_block = current_block->next;
    }

    printf("Blockchain Test Complete\n");
}

void validate_block(blockchain_pos *chain, uint32_t index) {
    struct block *current_block = chain->blocks;

    for (int i = 0; i < index; i++) {
        current_block = current_block->next;
    }

    bigint p1 = bigint_from_string(current_block->hash);
    bigint p2 = bigint_from_string(current_block->data);

    bigint n = bigint_mul(p1, p2);
    bigint t = totient(p1, p2);

    bigint e = current_block->public_key;

    char *tmp_signature = encrypt_text(current_block->data, e, n);

    if (strcmp(current_block->signature, tmp_signature) != 0) {
        printf("Block %d is invalid\n", index);
        current_block->valid = false;
    } else {
        printf("Block %d is valid\n", index);
        current_block->valid = true;
    }

    bigint_delete(p1);
    bigint_delete(p2);
    bigint_delete(n);
    bigint_delete(t);
    bigint_delete(e);
    free(tmp_signature);
}