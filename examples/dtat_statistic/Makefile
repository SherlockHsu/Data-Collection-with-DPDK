CC		= gcc
SRCS = $(wildcard *.c ../../src/*.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
INCS = -I../../inc
DEST	= main
CFLAGS	= -Wall -m64

$(DEST) : $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(INCS)

%.o : %.c
	$(CC) -o $@ -c $< $(INCS)

.PHONY:clean
clean:
	rm -f $(DEST) $(OBJS) *.txt