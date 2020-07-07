/* $Id: ex7.c,v 1.1 2020/05/12 03:19:02 mbsd Exp $ */

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
 * Atividade Parcial - Exercício 7
 */
int
main(void)
{
	/* código do produto e a quantidade */
	int cod;
	float qtd;
	float preco; 	/* preço obtido pelo codigo do produto */
	float preco_u;	/* preco unitário */
	float preco_t;	/* preço total */
	float desconto;	/* valor do desconto */

	cod = 0;
	qtd = 0;
	preco = 0;
	preco_u = 0;
	preco_t = 0;
	desconto = 0;

	/* obtemos o preço do produto */
	printf("Digite o código do produto: ");
	scanf("%d", &cod);
	printf("Digite a quantidade comprada: ");
	scanf("%f", &qtd);

	if (qtd <= 0) {
		printf("Quantidade tem que ser maior que 0\n");
		return (1);
	}

	/* checamos conforme a tabela 1 */
	if (cod >= 1 && cod <= 10) {
		preco_u = 10.0;
		preco = qtd * preco_u;
	} else if (cod >= 11 && cod <= 20) {
		preco_u = 15.0;
		preco = qtd * preco_u;
	} else if (cod >= 21 && cod <= 30) {
		preco_u = 20.0;
		preco = qtd * 20.0;
	} else {
		printf("Código de produto: %d inválido\n", cod);
		return (1);
	}

	/* checamos conforme a tabela 2 */
	if (preco <= 250.0) {
		desconto = (preco * 0.05);
		preco_t = preco - desconto;
	} else if (preco > 250.0 && preco <= 500.0) {
		desconto = (preco * 0.10);
		preco_t = preco - desconto;
	} else {
		desconto = (preco * 0.15);
		preco_t = preco - desconto;
	}

	printf("O preço unitário do produto: %.2f\n", preco_u);
	printf("O preço total da nota do produto: %.2f\n", preco);
	printf("O valor de desconto: %.2f\n", desconto);
	printf("O preço final: %.2f\n", preco_t);

	return (0);
}
