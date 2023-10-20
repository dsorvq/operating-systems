SRCS = wzip.c
TARG = wzip

CC = gcc
OPTS = -Wall -Werror -g
LIBS = -lm

OBJS = $(SRCS:.c=.o)

all: $(TARG)

$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARG)

