DOC		= doc.tex
PDF_READER	:= mupdf
TEX2PDF		:= texi2pdf

.PHONY: open all clean

open:
	$(PDF_READER) $(DOC) &
all:
	$(TEX2PDF) $(DOC) && pkill -HUP $(PDF_READER)
	#makeglossaries doc
	#$(TEX2PDF) $(DOC) && pkill -HUP $(PDF_READER)
clean:
	rm -f *.acn *.alg *.bbl *.glg *.gls *.ist \
		*.log *.out *.acr *.aux *.blg *.glo \
	   	*.glsdefs *.lof *.lot *.toc
