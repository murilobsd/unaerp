/* $Id: ex3.c,v 1.1 2020/05/12 03:19:02 mbsd Exp $ */

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
 * Atividade Parcial - Exercício 3
 */
int
main(void)
{
	float		altura;		/* armazeno a altura */
	char		genero;		/* armazeno genero */
	float		peso_ideal;	/* armzenamento peso_ideal */

	altura 		= 0;
	peso_ideal 	= 0;

	printf("Digite a altura: ");
	scanf("%f", &altura);
	printf("Escolha o genêro: (f)eminino/(m)masculino: ");
	scanf(" %c", &genero);

	/*
	 * checos os genêros possíveis, pode usar letras maísculas
	 */
	if (genero == 'm' || genero == 'M')
		peso_ideal = (72.7 * altura) - 58;
	else if (genero == 'f' || genero == 'F')
		peso_ideal = (62.1 * altura) - 44.7;
	else {
		printf("Genêro: %c inválido\n", genero);
		return (1);
	}

	printf("Peso ideal: %.2f para altura: %.2f e genêro: %c\n", peso_ideal,
	    altura, genero);

	return (0);
}
