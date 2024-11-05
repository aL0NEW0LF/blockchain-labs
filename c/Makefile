CC         = gcc
OBJ_DIR    = ./obj
SRC_DIR    = ./src
INCL_DIR   = ./include
OBJECTS    = $(addprefix $(OBJ_DIR)/, mtree.o sha256.o digest_sha256.o blockchain.o blockchain-pos.o the_hash.o)
INCLUDES   = $(addprefix $(INCL_DIR)/, mtree.h sha256.h digest_sha256.h blockchain.h blockchain-pos.h the_hash.h)
CFLAGS     = -g -Wall
EXECUTABLES = hash_test blockchain_test

hash_test: $(SRC_DIR)/hash_test.c $(OBJECTS)
		$(CC) $(CFLAGS) $< $(OBJECTS) -o hash_test -I $(INCL_DIR) -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	$(CC) $(CFLAGS) -I $(INCL_DIR) -c $< -o $@

blockchain_test: $(SRC_DIR)/blockchain_test.c $(OBJECTS)
		$(CC) $(CFLAGS) $< $(OBJECTS) -o blockchain_test -I $(INCL_DIR) -lm

clean:
	rm -f $(OBJECTS)
	rm -rf $(EXECUTABLES)