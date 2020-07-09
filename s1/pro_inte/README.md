<p align="center">
	<img src="https://github.com/murilobsd/unaerp/blob/master/s1/pro_inte/cliente/assets/logo.png">
</p>

[![license](https://img.shields.io/badge/License-BSD-blue.svg?style=for-the-badge)](LICENSE)

# Projeto Integrador

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

```
$ mupdf doc/doc.pdf
```

## Grupo

- João Victor
- Rannieri
- Miguel
- Murilo Ijanc'

## TODO

- [x] Cliente Websocket
- [x] Servidor Websocket
- [x] Código ESP8266
- [x] Hardware
