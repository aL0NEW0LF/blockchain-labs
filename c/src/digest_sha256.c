#include "../include/digest_sha256.h"
#include <stdint.h>

char *digest_sha256(char *data){
    size_t len = strlen(data);
    SHA256_CTX ctx;
    BYTE hash[SHA256_BLOCK_SIZE];
    char *hash_str = malloc(SHA256_BLOCK_SIZE * 2 + 1);
    strcpy(hash_str, "");

    sha256_init(&ctx);
    sha256_update(&ctx, data, len);
    sha256_final(&ctx, hash);

    char *tmp = malloc(3);
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
        sprintf(tmp, "%02x", hash[i]);
        strcat(hash_str, tmp);
    }

    return hash_str;
}

unsigned char *binary_to_char(int *binary) {
    unsigned char *str = malloc(SHA256_BLOCK_SIZE + 1);
    for (uint32_t i = 0; i < SHA256_BLOCK_SIZE; i++) {
        str[i] = 0;
        for (uint32_t j = 0; j < 8; j++)
        {
            str[i] += binary[i*8 + j] << j;
        }
    }
    str[SHA256_BLOCK_SIZE] = '\0';
    return str;
}

char *get_concat_hash(unsigned char* s1, unsigned char* s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);

    char *hash = digest_sha256(result);

    return hash;
}