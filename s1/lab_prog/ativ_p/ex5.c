/* $Id: ex5.c,v 1.1 2020/05/12 03:19:02 mbsd Exp $ */

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
 * Atividade Parcial - Exercício 5
 */
int
main(void)
{
	/* preco e novo preco*/
	float preco;
	float npreco;

	preco = 0;
	npreco = 0;

	/* obtemos o preço do produto */
	printf("Digite o preço do produto Ex. 50.0: ");
	scanf("%f", &preco);

	if (preco <= 0) {
		printf("O preço precisa ser positivo\n");
		return (1);
	}

	if (preco <= 50.0)
		npreco = preco + (preco * 0.05);
	else if (preco > 50.0 &&  preco <= 100.0)
		npreco = preco + (preco * 0.10);
	else
		npreco = preco + (preco * 0.15);

	printf("O novo preço do produto: %.2f\n", npreco);

	if (npreco <= 80.0)
		printf("Barato\n");
	else if (npreco > 80.0 && npreco <= 120.0)
		printf("Normal\n");
	else if (npreco > 120.0 && npreco <= 200.0)
		printf("Caro\n");
	else
		printf("Muito caro\n");

	return (0);
}
