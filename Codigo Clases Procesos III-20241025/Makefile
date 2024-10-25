SRCS = $(wildcard *.c)

all: $(SRCS:.c=)
CFLAGS= -O0

.c:
	gcc $(CFLAGS) $< -o $@

clean:
	rm $(SRCS:.c=)
