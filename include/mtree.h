#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "../include/digest_sha256.h"

struct mt_level_list {
    uint32_t len;
    char **hash;
};  

typedef struct {
    uint32_t LEVEL_COUNT;
    uint32_t LEAF_COUNT;
    uint32_t NODE_COUNT;
    struct mt_level_list *levels;    
} mt_list;

void construct_empty_tree(mt_list *tree, int num_transactions);
void deconstruct_tree(mt_list *tree);
void populate_tree(mt_list *tree, char **transactions);
void tree_test(mt_list *tree);