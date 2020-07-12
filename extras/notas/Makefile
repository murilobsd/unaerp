.SUFFIXES: .c .o

.ifdef DEBUG
CFLAGS	= -O0 $(PIPE) $(DEBUG)
.endif

CFLAGS	+= -I/usr/local/include 
LDADD 	+= -L/usr/local/lib -lcurl

.c.o:
	${CC} ${CFLAGS} -c $<

main: http.o main.o
	${CC} ${CFLAGS} ${LDADD} -o $@ main.o http.o

clean:
	rm -f main *.o
