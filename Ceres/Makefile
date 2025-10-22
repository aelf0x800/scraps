TARGET = ceres
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g
SRCS = \
	src/error.c \
	src/main.c \
	src/lexer.c \
	src/sema.c \
	src/source.c \
	src/stack.c \
	src/token.c 

build:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm $(TARGET)
