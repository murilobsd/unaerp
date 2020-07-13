[![license](https://img.shields.io/badge/License-BSD-blue.svg?style=for-the-badge)](LICENSE)

# Unaerp

Programa para obter as notas do boletim de um determinado aluno.

<p align="center">
<img alt="notas saida" src="https://github.com/murilobsd/unaerp/raw/master/extras/notas/notas.png">
</p>

## Requisitos

- json-c - [https://github.com/json-c/json-c](https://github.com/json-c/json-c)
- libcurl - [http://curl.haxx.se/libcurl/c](http://curl.haxx.se/libcurl/c)

## Build

```
$ make unaerp
```

## Run

```
$ ./unaerp <ra number> <password>
$ ./unaerp 123456 123456
Disciplina: ENGENHARIA DE SOFTWARE I Atividade Parcial: 10,0
Disciplina: INTERACAO HUMANO COMPUTADOR Atividade Parcial: 9,5
,,,
```

## Clean

```
$ make clean
```
