/* $Id: ex2.c,v 1.1 2020/05/12 03:19:02 mbsd Exp $ */

/*
 * Copyright (c) 2020 Murilo Ijanc' <mbsd@m0x.ru>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>

/*
 * Atividade Parcial - Exercício 2
 */
int
main(void)
{
	/* */
	int num1, num2;
	int opcao;
	int resultado;

	num1 = 0;
	num2 = 0;
	opcao = 0;
	resultado = 0;

	/* Recebendo os dados de cada candidato 1..5 */
	printf("Digite o primeiro número: ");
	scanf("%d", &num1);
	printf("Digite o segundo número: ");
	scanf("%d", &num2);
	printf("\n\n");
	printf("1. Média entre dois números\n");
	printf("2. Diferença do maior pelo menor\n");
	printf("3. Produto entre os números digitados\n");
	printf("4. Divisão do primeiro pelo segundo\n");
	printf("Digite um dos números das operações acima: ");
	scanf("%d", &opcao);

	if (opcao <= 0 || opcao > 4) {
		printf("Opção %d inválida\n", opcao);
		return (1);
	}

	if (opcao == 4 && num2 == 0) {
		printf("Não é possível divisão por zero");
		return (1);
	}

	if (opcao == 1) {
		resultado = (num1 + num2) / 2;
		printf("Média de %d e %d igual %d\n", num1, num2, resultado);
	} else if (opcao == 2) {
		resultado = (num1 - num2);
		printf("Diferença de %d por %d igual %d\n", num1, num2,
		    resultado);
	} else if (opcao == 3) {
		resultado = (num1 * num2);
		printf("Produto de %d por %d igual %d\n", num1, num2, resultado);
	} else if (opcao == 4) {
		resultado = (num1 / num2);
		printf("Divisão de %d por %d igual %d\n", num1, num2, resultado);
	}

	return (0);
}
