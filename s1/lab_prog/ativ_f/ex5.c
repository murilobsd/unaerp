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

#define MAX_ALUNOS 	10
#define PARADA 		-1.0
#define PESO_P 		0.40	/* peso da nota parcial */
#define PESO_F 		0.60	/* peso da nota final */
#define MEDIA		5.0	/* aluno passa acima */

int
main(int argc, char *argv[])
{
	float 	medias_finais[MAX_ALUNOS] = {0};
	float 	notas_finais[MAX_ALUNOS] = {0};
	float 	notas_parciais[MAX_ALUNOS] = {0};
	float	valor = 0.0;
	int 	count = 0;
	int 	i = 0;

	printf("\n** Digite -1 na nota parcial ou final para parar. **\n");

	while (count < MAX_ALUNOS) {
		printf("Digite nota parcial do aluno[%d]: ", count+1);
		scanf("%f", &valor);

		if (valor == PARADA)
			break;

		notas_parciais[count] = valor;
		valor = 0.0;

		printf("Digite a nota final do aluno[%d]: ", count+1);
		scanf("%f", &valor);

		if (valor == PARADA)
			break;

		notas_finais[count] = valor;

		/* calculando média ponderada final */
		medias_finais[count] = (notas_parciais[count] * PESO_P) +
		    (notas_finais[count] * PESO_F);

		valor = 0.0;
		count++;
	}

	printf("\n\n");

	while (i < count) {
		if (medias_finais[i] >= MEDIA)
			printf("Aluno %d média: %.2f: aprovado\n", i,
			    medias_finais[i]);
		else
			printf("Aluno %d média: %.2f: reprovado\n", i,
			    medias_finais[i]);
		i++;
	}

	return (0);
}
