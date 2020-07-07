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

#define MAX_PRODUTOS 	100
#define PARADA 		-1.0

int
main(int argc, char *argv[])
{
	/* vetor de contentdo os valores dos produtos */
	float 	produtos[MAX_PRODUTOS] = {0};
	float 	valor = 0;
					/* valor do produto */

	int 	qtd_inferior = 0; 	/* produtos com valor inferior 50.0 */
	int 	qtd_media = 0;		/* produtos com valor entre 50 e 500 */
	int 	qtd_superior = 0;	/* produtos com valor superior a 500 */

	int 	count = 0;
	int 	i = 0;


	printf("\n\n** Para parar o programa digite: -1.0 **\n");
	printf("** Só serão permitidos no máximo %d produtos **\n\n",
	    MAX_PRODUTOS);

	while (count < MAX_PRODUTOS) {

		printf("Digite o valor para o produto[%d]: ", count+1);
		scanf("%f", &valor);

		if (valor != PARADA) {
			produtos[count] = valor;
			count += 1;
			/* zeramos o valor para próxima iteração */
			valor = 0;
		} else {
			valor = 0;
			break;
		}

	}

	if (count == 0) {
		printf("Não foi digitado nenhum produto.\n");
		return (0);
	}

	for (i = 0; i < count; i++) {
		if (produtos[i] <= 50.0)
			qtd_inferior += 1;
		else if (produtos[i] > 50.0 && produtos[i] < 500.0)
			qtd_media += 1;
		else
			qtd_superior += 1;
	}

	printf("\n\nQuantidade de produtos com valor inferior a R$ 50.00: %d\n",
	    qtd_inferior);
	printf("Quantidade de produtos com valor maior que R$ 50.00 e menor que"
	    "R$ 500.0: %d\n", qtd_media);
	printf("Quantidade de produtos com valor superior a R$ 500.00: %d\n",
	    qtd_superior);

	return (0);
}
