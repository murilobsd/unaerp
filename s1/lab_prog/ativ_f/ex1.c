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

int
main(int argc, char *argv[])
{
	int count_impares = 0;
	int count_pares = 0;
	int i = 0;
	int qtd_num_impares = 0;
	int qtd_num_pares = 0;
	int vetor[10];
	int vetor_impares[10];
	int vetor_pares[10];

	for (i = 0; i < 10; i++) {
		printf("VETOR[%d]: ", i+1);
		scanf("%d", &vetor[i]);
	}

	for (i = 0; i < 10; i++) {
		if (vetor[i] % 2 == 0) {
			vetor_pares[count_pares] = vetor[i];
			qtd_num_pares += 1;
			count_pares += 1;
		} else {
			vetor_impares[count_impares] = vetor[i];
			qtd_num_impares += 1;
			count_impares += 1;

		}
	}

	printf("Quantidade de números pares é de %d\n", qtd_num_pares);
	for (i = 0; i < count_pares; i++) {
		if (i == count_pares - 1)
			printf("%d\n", vetor_pares[i]);
		else
			printf("%d, ", vetor_pares[i]);
	}

	printf("Quantidade de números impares é de %d\n", qtd_num_impares);
	for (i = 0; i < count_impares; i++) {
		if (i == count_impares - 1)
			printf("%d\n", vetor_impares[i]);
		else
			printf("%d, ", vetor_impares[i]);
	}
	return (0);
}
