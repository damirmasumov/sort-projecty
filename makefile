CC = gcc
TARGET = stack_sort
SRCS = main.c func.c insertion_sort.c merge_sort.c
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)
clean:
	rm -f $(TARGET)
run:
	./$(TARGET)
all: $(TARGET)
.PHONY: clean run all