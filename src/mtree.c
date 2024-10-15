#include "../include/mtree.h"

void construct_empty_tree(mt_list *tree, int num_transactions) {
    tree->LEAF_COUNT = num_transactions;
    /* tree->NODE_COUNT = pow(2, ceil(log2(tree->LEAF_COUNT))); */

    tree->LEVEL_COUNT = ceil(log2(tree->LEAF_COUNT)) + 1;

    tree->levels[0].len = tree->LEAF_COUNT;
    tree->levels[0].hash = malloc(tree->LEAF_COUNT * sizeof(char *));
    for (uint32_t i = 0; i < tree->LEAF_COUNT; i++) {
        tree->levels[0].hash[i] = malloc(SHA256_BLOCK_SIZE);
    }

    for (uint32_t i = 1; i < tree->LEVEL_COUNT; i++) {
        tree->levels[i].len = tree->levels[i-1].len / 2 + tree->levels[i-1].len % 2;
        tree->levels[i].hash = malloc(tree->levels[i].len * sizeof(char *));
        for (uint32_t j = 0; j < tree->levels[i].len; j++) {
            tree->levels[i].hash[j] = malloc(SHA256_BLOCK_SIZE);
        }
    }
}

void deconstruct_tree(mt_list *tree) {
    for (uint32_t i = 0; i < tree->LEVEL_COUNT; i++) {
        free(tree->levels[i].hash);
    }

    printf("Tree deconstructed\n");
}

void populate_tree(mt_list *tree, char **transactions) {
    uint32_t i;

    for (i = 0; i < tree->LEAF_COUNT; i++) {
        tree->levels[0].hash[i] = digest_sha256(transactions[i]);
    }

    for (i = 1; i < tree->LEVEL_COUNT; i++) {
        for (uint32_t j = 0; j < tree->levels[i].len; j++) {
            if (j * 2 + 1 < tree->levels[i-1].len) {
                tree->levels[i].hash[j] = get_concat_hash(tree->levels[i - 1].hash[j * 2], tree->levels[i - 1].hash[j * 2 + 1]);
            } else {   
                tree->levels[i].hash[j] = tree->levels[i - 1].hash[j * 2];
            }            
        }
    }

    printf("Tree populated\n");
}

void tree_test(mt_list *tree) {
    printf("LEVEL_COUNT: %d\n", tree->LEVEL_COUNT);
    printf("LEAF_COUNT: %d\n", tree->LEAF_COUNT);
    printf("NODE_COUNT: %d\n", tree->NODE_COUNT);
    for (uint32_t i = 0; i < tree->LEVEL_COUNT; i++) {
        printf("Level %d: %d\n", i, tree->levels[i].len);
        for (uint32_t j = 0; j < tree->levels[i].len; j++) {
            printf("%s\n", tree->levels[i].hash[j]);
        }
    }
}