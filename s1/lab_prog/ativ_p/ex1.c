/* $Id: ex1.c,v 1.2 2020/05/16 17:49:01 mbsd Exp $ */

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
 * Atividade Parcial - Exercício 1
 */
int
main(void)
{
	/* Número dos candidatos e total de votos por candidatos */
	int ncand_1;
	int ncand_2;
	int ncand_3;
	int ncand_4;
	int ncand_5;

	float totv_1;
	float totv_2;
	float totv_3;
	float totv_4;
	float totv_5;

	int total_votos;	/* armazena total de votos */
	int cand_maxv;		/* armazena o candidato com vencedor */
	int cand_minv;		/* armazena o candidato com menor número
				   de votos*/
	/* inicializo as variáveis */
	ncand_1 = 0;
	ncand_2 = 0;
	ncand_3 = 0;
	ncand_4 = 0;
	ncand_5 = 0;

	totv_1 = 0;
	totv_2 = 0;
	totv_3 = 0;
	totv_4 = 0;
	totv_5 = 0;

	total_votos = 0;
	cand_maxv = 0;
	cand_minv = 0;

	/* Recebendo os dados de cada candidato 1..5 */
	printf("Digite o número candidato 1: ");
	scanf("%d", &ncand_1);
	printf("Digite a quantidade total de votos do canditado 1: ");
	scanf("%f", &totv_1);

	printf("Digite o número candidato 2: ");
	scanf("%d", &ncand_2);
	printf("Digite a quantidade total de votos do canditado 2: ");
	scanf("%f", &totv_2);

	printf("Digite o número candidato 3: ");
	scanf("%d", &ncand_3);
	printf("Digite a quantidade total de votos do canditado 3: ");
	scanf("%f", &totv_3);

	printf("Digite o número candidato 4: ");
	scanf("%d", &ncand_4);
	printf("Digite a quantidade total de votos do canditado 4: ");
	scanf("%f", &totv_4);

	printf("Digite o número candidato 5: ");
	scanf("%d", &ncand_5);
	printf("Digite a quantidade total de votos do canditado 5: ");
	scanf("%f", &totv_5);

	/* Calculamos o total de votos */
	total_votos = totv_1 + totv_2 + totv_3 + totv_4 + totv_5;
	printf("O total de votos dos candidatos: %d\n", total_votos);

	/* Calculamos e exibimos o percentual de cada candidato */
	printf("O percentual do candidato [%d]: %.2f\n", ncand_1,
	    (totv_1 / total_votos) * 100.0);
	printf("O percentual do candidato [%d]: %.2f\n", ncand_2,
	    (totv_2 / total_votos) * 100.0);
	printf("O percentual do candidato [%d]: %.2f\n", ncand_3,
	    (totv_3 / total_votos) * 100.0);
	printf("O percentual do candidato [%d]: %.2f\n", ncand_4,
	    (totv_4 / total_votos) * 100.0);
	printf("O percentual do candidato [%d]: %.2f\n", ncand_5,
	    (totv_5 / total_votos) * 100.0);

	/* Candidato que teve maior voto */
	if (totv_1 > totv_2 && totv_1 > totv_3 && totv_1 > totv_4 &&
	    totv_1 > totv_5)
		cand_maxv = ncand_1;
	else if (totv_2 > totv_1 && totv_2 > totv_3 && totv_2 > totv_4 &&
	    totv_2 > totv_5)
		cand_maxv = ncand_2;
	else if (totv_3 > totv_1 && totv_3 > totv_2 && totv_3 > totv_4 &&
	    totv_3 > totv_5)
		cand_maxv = ncand_3;
	else if (totv_4 > totv_1 && totv_4 > totv_2 && totv_4 > totv_3 &&
	    totv_4 > totv_5)
		cand_maxv = ncand_4;
	else
		cand_maxv = ncand_5;
	printf("O candidato com maior número de votos é: %d\n", cand_maxv);

	/* Candidato que teve menor voto */
	if (totv_1 < totv_2 && totv_1 < totv_3 && totv_1 < totv_4 &&
	    totv_1 < totv_5)
		cand_minv = ncand_1;
	else if (totv_2 < totv_1 && totv_2 < totv_3 && totv_2 < totv_4 &&
	    totv_2 < totv_5)
		cand_minv = ncand_2;
	else if (totv_3 < totv_1 && totv_3 < totv_2 && totv_3 < totv_4 &&
	    totv_3 < totv_5)
		cand_minv = ncand_3;
	else if (totv_4 < totv_1 && totv_4 < totv_2 && totv_4 < totv_3 &&
	    totv_4 < totv_5)
		cand_minv = ncand_4;
	else
		cand_minv = ncand_5;

	printf("O candidato com menor número de votos é: %d\n", cand_minv);
	return (0);
}
