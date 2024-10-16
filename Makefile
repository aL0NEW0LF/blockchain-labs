CC         = gcc
OBJ_DIR    = ./obj
SRC_DIR    = ./src
INCL_DIR   = ./include
OBJECTS    = $(addprefix $(OBJ_DIR)/, mtree.o sha256.o digest_sha256.o blockchain.o)
INCLUDES   = $(addprefix $(INCL_DIR)/, mtree.h sha256.h digest_sha256.h blockchain.h)
CFLAGS     = -g -Wall
EXECUTABLE = main

$(EXECUTABLE): $(SRC_DIR)/main.c $(OBJECTS)
	$(CC) $(CFLAGS) $< $(OBJECTS) -o $(EXECUTABLE) -I $(INCL_DIR) -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	$(CC) $(CFLAGS) -I $(INCL_DIR) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -rf $(EXECUTABLE)*