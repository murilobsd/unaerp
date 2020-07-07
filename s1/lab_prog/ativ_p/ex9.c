/* $Id: ex9.c,v 1.3 2020/05/12 18:28:26 mbsd Exp $ */

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
 * Atividade Parcial - Exercício 9
 */
int
main(void)
{
	int 	cod;		/* código do estado de origem */
	int 	cod_c;		/* código da carga */
	float 	peso;		/* peso em toneladas do caminhão + carga */
	float	peso_kg;	/* peso em quilograma da carga */
	float	preco_c;	/* preço da carga */
	float	valor_imp;	/* valor do imposto */

	/* inicializamos as variáveis */
	cod = 0;
	cod_c = 0;
	peso = 0;
	peso_kg = 0;
	preco_c = 0;
	valor_imp = 0;

	/* obtemos os dados de cód. de ori. peso da carga em t e cod. carga */
	printf("Digite o código do estado de origem, 1..5: ");
	scanf("%d", &cod);
	printf("Digite o peso em TONELADAS da carga: ");
	scanf("%f", &peso);
	printf("Digite o código da carga, 10..40: ");
	scanf("%d", &cod_c);

	/*
	 * Algumas validações
	 */

	/* checamos o código de origem */
	if (cod <= 1 && cod >= 5) {
		printf("O código de origem deve estar entre 1 e 5.\n");
		return (1);
	}

	/* checamos o codigo da carga */
	if (cod_c < 10 && cod > 40) {
		printf("O código da carga deve estar entre 10 e 40.\n");
		return (1);
	}

	/* checamos se o peso é positivo */
	if (peso <= 0) {
		printf("O peso necessita ser positivo.\n");
		return (1);
	}

	/*
	 * Calculos
	 */

	/* peso da carga em quilogramas */
	peso_kg = peso / 0.0010;
	printf("O peso da carga: %.2fKg\n", peso_kg);

	/* preço da carga */
	/*
	 * TODO: Na tabela o codigo da carga está 10 a 20 (incluindo 10 e 20)
	 * mas no exercício é passado que o código da carga está entre 10 e 40
	 * (exclusivo).
	 */
	if (cod_c >= 10 && cod_c <= 20)
		preco_c = 100.0 * peso_kg;
	else if (cod_c >= 21 && cod_c <= 30)
		preco_c = 250.0 * peso_kg;
	else if (cod_c >= 31 && cod_c <= 40)
		preco_c = 340.0 * peso_kg;
	printf("O preço da carga: R$ %.2f\n", preco_c);

	/* valor do imposto */
	switch(cod) {
	case 1:
		valor_imp = preco_c * 0.35;
	case 2:
		valor_imp = preco_c * 0.25;
	case 3:
		valor_imp = preco_c * 0.15;
	case 4:
		valor_imp = preco_c * 0.05;
	case 5:
		valor_imp = preco_c * 0;
	}
	printf("O valor do imposto: R$ %.2f\n\n", valor_imp);

	/* valor total */
	printf("O valor total: R$ %.2f\n", preco_c + valor_imp);

	return (0);
}
