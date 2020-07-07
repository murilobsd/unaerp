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

/* Número de vendedores da empresa */
#define NUM_VENDEDORES 	6

int
main(int argc, char *argv[])
{
	float	maior_comissao = 0.0;
	float	somatoria_vendas = 0.0;
	float 	comissoes[NUM_VENDEDORES] = {0};
	float 	total_vendas[NUM_VENDEDORES] = {0};
	int 	count = 0;

	while (count < NUM_VENDEDORES) {
		float comissao = 0;

		printf("Digite o total de vendas do vendedor %d: ", count+1);
		scanf("%f", &total_vendas[count]);

		printf("Digite o percentual de comissão do vendedor %d: ",
		    count+1);
		scanf("%f", &comissao);

		/* adicionamos a comissao Ex. 15% -> venda * (15 / 100.0) */
		comissoes[count] = total_vendas[count] * (comissao / 100.0);

		count +=1;
	}

	count = 0;
	printf("\n\n");

	while (count < NUM_VENDEDORES) {
		printf("Comissão do vendor %d: %.2f\n", count+1,
		    comissoes[count]);

		if (comissoes[count] > maior_comissao)
			maior_comissao = comissoes[count];

		somatoria_vendas += total_vendas[count];

		count +=1;
	}

	printf("Maior comissão a receber: %.2f\n", maior_comissao);
	printf("Somatória das vendas: %.2f\n", somatoria_vendas);

	return (0);
}
