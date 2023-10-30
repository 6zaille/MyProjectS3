CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lSDL2 -lSDL2_image

SRC = rotation_image.c
OBJ = $(SRC:.c=.o)
EXEC = rotation_image

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
