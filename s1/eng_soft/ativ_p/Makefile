.PHONY: all clean

all:
	bibtex doc/doc.aux
	makeglossaries doc
	texi2pdf doc/doc.tex -o doc/doc.pdf

clean:
	rm -f *.dvi *.acn *.alg *.bbl *.glg *.gls *.ist \
		*.log *.out *.acr *.aux *.blg *.glo \
	   	*.glsdefs *.lof *.lot *.toc
