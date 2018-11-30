CC		= gcc
SRCS = $(wildcard *.c ../../src/*.c)
OBJS = $(SRCS:.c = .o)
INCS = -I../../inc
DEST	= main
CFLAGS	= -Wall -m64

$(DEST): $(OBJS)
	$(CC) -o $(DEST) $(OBJS) $(CFLAGS) $(INCS)

.PHONY:clean
clean:
	rm -f $(DEST) $(OBJS) *.txt