CC = gcc
CFLAGS = -Wal -gcc
LIBS = -lpthread
TARGET = shttpd
RM = rm -f
OBJS = shttpd.o

all: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} ${LIBS}

clean:
	${RM} ${TARGET} ${OBJS}
