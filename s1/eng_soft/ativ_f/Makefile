.PHONY: cinema all clean doc

CFLAGS 	:= -std=c89 -O2 -Wall

SRCS	:= cinema.c

OUTS	:= cinema

${OUTS}: ${SRCS}
	${CC} ${CFLAGS} -o $@ $<

doc:
	texi2pdf doc/doc.tex -o doc/doc.pdf

all: ${OUTS}

clean:
	@rm -f ${OUTS} *.lof *.log *.out *.toc *.aux
