#include "../include/the_hash.h"

#define GENNUM(a, b) ((a << 32) | (a >> 32)) ^ b

char *string_to_binary(char *s) {
    if(s == NULL) return 0;
    size_t len = strlen(s);
    char *binary = malloc(len*8 + 1);
    binary[0] = '\0';
    for(size_t i = 0; i < len; ++i) {
        char ch = s[i];
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
    return binary;
}

char *binary_to_string(char *binary) {
    if(binary == NULL) return 0;
    size_t len = strlen(binary);
    char *s = malloc(len/8 + 1);
    s[0] = '\0';
    for(size_t i = 0; i < len; i += 8) {
        char byte[9];
        byte[8] = '\0';
        for(int j = 0; j < 8; ++j) {
            byte[j] = binary[i+j];
        }
        s[i/8] = strtol(byte, 0, 2);
    }
    return s;
}

void binary_to_alphanumeric(char *hash, char *output) {
    const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < 32; i++) {
        uint8_t value = 0;
        for (int j = 0; j < 8; j++) {
            value = (value << 1) | (hash[i * 8 + j] - '0');
        }
        output[i] = alphabet[value % 62];
    }
    output[32] = '\0';
}

uint64_t gen_num(char *s) {
    if(s == NULL) return 0;
    size_t len = strlen(s);
    uint64_t hash = 0;
    for(size_t i = 0; i < len; ++i) {
        hash = GENNUM(hash, s[i]);
    }
    return (hash % 8) + 1;
}

char *hash_string(char *str) {
    if (str == NULL) return 0;

    char *binary = string_to_binary(str);
    uint64_t string_len = strlen(str);

    // padding
    uint64_t gened_num = gen_num(binary);
    uint64_t padding_before_len = 256 - (string_len % 256);
    uint64_t padding_after_len = gened_num * 256;
    printf("gened_num %ld \n", gened_num);
    printf("padding_before_len %ld \n", padding_before_len);
    printf("padding_after_len %ld \n", padding_after_len);

    uint64_t total_padding_len = padding_before_len + string_len * 8 + padding_after_len;

    char *padding = malloc(total_padding_len + 1);
    if (padding == NULL) {
        perror("malloc failed");
        return NULL;
    }

    // padding before
    for (uint64_t i = 0; i < padding_before_len; i++) {
        padding[i] = (i % 2 == 0) ? '1' : '0';
    }

    // copy binary
    for (uint64_t i = 0; i < string_len*8; i++) {
        padding[padding_before_len + i] = binary[i];
    }

    // padding after
    for (uint64_t i = 0; i < padding_after_len - 1; i++) {
        padding[padding_before_len + string_len * 8 + i] = (i % 2 == 0) ? '1' : '0';
    }

    padding[padding_before_len + string_len * 8 + padding_after_len - 1] = '1';
    padding[padding_before_len + string_len * 8 + padding_after_len] = '\0';

    free(binary);
    binary = NULL;

    uint64_t blocks_count = (string_len + padding_before_len + padding_after_len) / 256;
    
    // 256 bit hash
    char *hash = malloc(256 + 1);
    if (hash == NULL) {
        perror("malloc failed");
        free(padding);
        return NULL;
    }

    for (uint64_t i = 0; i < 256; i++){
        hash[i] = (i % 2 == 0) ? '1' : '0';

        for (uint64_t j = 0; j < blocks_count; j++) {
            hash[i] = hash[i] ^ padding[j * 256 + i];
        }
    }

    hash[256] = '\0';

    printf("padding: %s\n", padding);
    printf("hash: %s\n", hash);

    char *alphanumeric_hash = malloc(33);
    if (alphanumeric_hash == NULL) {
        perror("malloc failed");
        free(padding);
        free(hash);
        return NULL;
    }
    binary_to_alphanumeric(hash, alphanumeric_hash);

    free(padding);
    free(hash);

    return alphanumeric_hash;
}

void brute_force(char *hash) {
    const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char *brute = malloc(33);
    brute[32] = '\0';

    int i = 0;
    int c = 0;
    int nbAllowed = 62;
    printf("%d\n", nbAllowed);

    while (strcmp(hash, brute) != 0) {
        for(i = 0; i < 32; i++) {
            c = rand() % nbAllowed ;
            brute[i] = alphabet[c];
        }

        printf("\r%s", brute);
    }

    printf("\n");
    printf("brute: %s\n", brute);
    free(brute);
    brute = NULL;
    free(alphabet);
    alphabet = NULL;
}