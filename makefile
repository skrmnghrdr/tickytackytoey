# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = tictactoe
SOURCE = tickytackytoey.c

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Clean up compiled files
clean:
	rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
