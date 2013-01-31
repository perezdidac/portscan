
TARGET := bin/portscan

SOURCES := $(wildcard src/*.c)
OBJS := $(SOURCES:.c=.o)

CFLAGS +=

all: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
