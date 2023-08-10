CC = gcc
LDPATH = -L/${HOME}/Code/C/bonepong
LDFLAGS = -lm -ldl -lSDL2main -lSDL2 -lSDL2_image -lbonemath
CFLAGS = -c -Wall -Werror
OBJS = pong.o
WBIN = pong.obj
NAME = bonepong

all: bonepong

pong: $(OBJS)
	$(CC) $(LDPATH) $(OBJS) $(LDFLAGS) -o $(NAME)

pong.o: pong.c
	$(CC) $(CFLAGS) pong.c

clean:
	rm *.o $(NAME)

edit:
	vim -O pong.c pong.c
