.PHONY: s1 all clean

s1:
	@echo "Compilando Semestre 1 - Lab. Programação"
	make -C s1/lab_prog/ativ_p/ all
	make -C s1/lab_prog/ativ_f/ all

all: s1

clean:
	make -C s1/lab_prog/ativ_p/ clean
	make -C s1/lab_prog/ativ_f/ clean
