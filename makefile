
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = stack_sort
SRCS = main.c func.c insertion_sort.c merge_sort.c
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
clean:
	rm -f $(TARGET)
run: $(TARGET)
	./$(TARGET)
all: run
.PHONY: clean run all