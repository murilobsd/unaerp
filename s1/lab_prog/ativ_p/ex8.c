/* $Id: ex8.c,v 1.1 2020/05/12 03:19:02 mbsd Exp $ */

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
 * Atividade Parcial - Exercício 8
 */
int
main(void)
{
	float medida;
	char tipo_conv; /* conversão */

	medida = 0;

	printf("Por favor entre com o valor da medida em metros: ");
	scanf("%f", &medida);
	printf("(m)milímetro\n");
	printf("(c)centimetro\n");
	printf("(q)uilômetro\n");
	printf("Selecione uma das conversões: (m, c, q): ");
	scanf(" %c", &tipo_conv);

	if (medida <= 0) {
		printf("Medida necessita ser positiva\n");
		return (1);
	}

	if (tipo_conv == 'm')
		printf("O valor: %.2fm em milímetro(s): %.3fmm\n", medida,
		    medida / 0.001);
	else if (tipo_conv == 'c')
		printf("O valor: %.2fm em centímero(s): %.3fcm\n", medida,
		    medida / 0.01);
	else if (tipo_conv == 'q')
		printf("O valor: %.2fm em quilômetro(s): %.3fkm\n", medida,
		    medida / 1000.0);
	else {
		printf("Tipo: %c inválido\n", tipo_conv);
		return (1);
	}

	return (0);
}
