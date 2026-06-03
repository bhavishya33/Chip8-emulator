CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lSDL2

# Your target executable name
TARGET = chip8

# Your separated source files
SOURCES = main.c emulator_decode_ins.c emulator_setup.c input_handling.c monitor.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)