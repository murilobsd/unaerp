/* $Id: ex4.c,v 1.1 2020/05/12 03:19:02 mbsd Exp $ */

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
 * Atividade Parcial - Exercício 4
 */
int
main(void)
{
	/* custos */
	float c_distribuidor;
	float c_fabrica;
	float c_impostos;
	float c_total;

	c_distribuidor = 0;
	c_fabrica = 0;
	c_impostos = 0;
	c_total = 0;

	/* obtemos o custo de fábrica para servir de base para os calculos */
	printf("Digite o valor do custo de fábrica do veículo Ex. 12345.0: ");
	scanf("%f", &c_fabrica);

	if (c_fabrica <= 0) {
		printf("O custo de fábrica precisa ser positivo\n");
		return (1);
	}

	if (c_fabrica <= 12000.0) {
		c_distribuidor = c_fabrica * 0.05;
		c_impostos = 0;
		c_total = c_fabrica + c_distribuidor + c_impostos;
	} else if (c_fabrica > 12000.0 && c_fabrica <= 25000.0) {
		c_distribuidor = c_fabrica * 0.10;
		c_impostos = c_fabrica * 0.15;
		c_total = c_fabrica + c_distribuidor + c_impostos;
	} else {
		c_distribuidor = c_fabrica * 0.15;
		c_impostos = c_fabrica * 0.20;
		c_total = c_fabrica + c_distribuidor + c_impostos;
	}

	printf("Custo total do véiculo: %.2f\n", c_total);

	return (0);
}
