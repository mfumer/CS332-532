
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = lab07

all: $(TARGET)

$(TARGET): lab07.o
	$(CC) $(CFLAGS) -o $(TARGET) lab07.o

lab07.o: lab07.c
	$(CC) $(CFLAGS) -c lab07.c

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
