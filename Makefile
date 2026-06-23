CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
SRC = src/main.c src/util.c src/user.c src/account.c src/transaction.c
OBJ = $(SRC:.c=.o)
TARGET = bank

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ): $(wildcard include/*.h)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
