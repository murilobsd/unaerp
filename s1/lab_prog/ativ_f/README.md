[![license](https://img.shields.io/badge/License-BSD-blue.svg?style=for-the-badge)](LICENSE)

# Atividade Final

## Testado em:

```
SO: OpenBSD 6.7 amd64

CLANG: OpenBSD clang version 8.0.1 (tags/RELEASE_801/final) (based on LLVM 8.0.1)
Target: amd64-unknown-openbsd6.7
Thread model: posix
InstalledDir: /usr/bin
```

## Build

O Makefile é suportado em sistemas [BSD](https://man.openbsd.org/make) e Linux
caso queira compilar em **Windows** sugiro que veja o código e tente adaptar.

```
$ make all
```

## Executando

Exemplo de execução do exercício 1:

```
$ ./ex1
```

## Documento

Para criar o documento é necessário ter a suíte do [texlive](https://tug.org/texlive/)

```
$ make doc
$ mupdf doc/doc.pdf
```

## TODO

- [x] Exercício 1
- [x] Exercício 2
- [x] Exercício 3
- [x] Exercício 4
- [x] Exercício 5
