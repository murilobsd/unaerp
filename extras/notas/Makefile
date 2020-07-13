.SUFFIXES: .c .o

.ifdef DEBUG
CFLAGS	= -O0 $(PIPE) $(DEBUG)
.endif

CFLAGS	+= -I/usr/local/include \
	-Wall -Werror
LDADD 	+= -L/usr/local/lib -lcurl -ljson-c

.c.o:
	${CC} ${CFLAGS} -c $<

unaerp: http.o unaerp.o main.o
	${CC} ${CFLAGS} ${LDADD} -o $@ http.o unaerp.o main.o

clean:
	rm -f unaerp *.o *.core
