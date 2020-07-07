.PHONY: ex1 ex2 ex3 ex4 ex5 ex6 ex7 ex8 ex9 ex10 all clean doc

CFLAGS 	:= -std=c89 -O2 -Wall

SRCS	:= ex1.c \
	  ex2.c \
	  ex3.c \
	  ex4.c \
	  ex5.c \
	  ex6.c \
	  ex7.c \
	  ex8.c \
	  ex9.c \
	  ex10.c \

OUTS	:= ex1 \
	   ex2 \
	   ex3 \
	   ex4 \
	   ex5 \
	   ex6 \
	   ex7 \
	   ex8 \
	   ex9 \
	   ex10 \

${OUTS}: ${SRCS}
	${CC} ${CFLAGS} -o $@ $<

doc:
	texi2pdf doc/doc.tex -o doc/doc.pdf

all: ${OUTS}

clean:
	@rm -f ${OUTS} *.lof *.log *.out *.toc *.aux
