/* $Id: ex6.c,v 1.1 2020/05/12 03:19:02 mbsd Exp $ */

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
 * Atividade Parcial - Exercício 6
 */
int
main(void)
{
	/* código de origem */
	int cod;

	cod = 0;

	/* obtemos o preço do produto */
	printf("Digite o códio de origem: ");
	scanf("%d", &cod);

	if (cod == 1)
		printf("Sul\n");
	else if (cod == 2)
		printf("Norte\n");
	else if (cod == 3)
		printf("Leste\n");
	else if (cod == 4)
		printf("Oeste\n");
	else if (cod == 5 || cod == 6)
		printf("Nordeste\n");
	else if (cod == 7 || cod == 8 || cod == 9)
		printf("Sudeste\n");
	else if (cod >= 10 && cod <= 20)
		printf("Centro-Oeste\n");
	else if (cod >= 21 && cod <= 30)
		printf("Noroeste\n");
	else
		printf("Código de origem: %d inválido\n", cod);

	return (0);
}
