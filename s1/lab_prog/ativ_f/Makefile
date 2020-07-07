.PHONY: ex1 ex2 ex3 ex4 ex5 all clean doc

CFLAGS 	:= -std=c89 -O2 -Wall

SRCS	:= ex1.c \
	   ex2.c \
	   ex3.c \
	   ex4.c \
	   ex5.c

OUTS	:= ex1 \
	   ex2 \
	   ex3 \
	   ex4 \
	   ex5

${OUTS}: ${SRCS}
	${CC} ${CFLAGS} -o $@ $<

doc:
	texi2pdf doc/doc.tex -o doc/doc.pdf

all: ${OUTS}

clean:
	@rm -f ${OUTS} *.lof *.log *.out *.toc *.aux
