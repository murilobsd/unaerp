/* $Id: ex10.c,v 1.2 2020/05/12 18:28:26 mbsd Exp $ */

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
 * Atividade Parcial - Exercício 10
 */
int
main(void)
{
	int	turno;		/* turno de trabalho matutino... */
	int	categoria;	/* categoria operario... */
	int 	num_horas;	/* horas de tabalho no mês */
	float 	salario_min;	/* salario minímo */
	float	salario_coe;	/* coefieciente salário */
	float	salario_brt;	/* salário bruto */
	float	salario_liq;	/* salário liquido */
	float	imposto;	/* valor do imposto */
	float	gratificacao;	/* gratificação */
	float	aux_alim;	/* auxio alimentacao */

	/* inicializamos as vairiáveis */
	turno = 0;
	categoria = 0;
	num_horas = 0;
	salario_min = 0;
	salario_coe = 0;
	salario_brt = 0;
	salario_liq = 0;
	imposto = 0;
	gratificacao = 0;
	aux_alim = 0;

	/* recebendo os dados */
	printf("Digite o valor do salário: ");
	scanf("%f", &salario_min);

	printf("1 - Matutino\n");
	printf("2 - Vespertino\n");
	printf("3 - Noturno\n");
	printf("Selecione o turno (1, 2 ou 3): ");
	scanf("%d", &turno);

	printf("\n1 - Operário\n");
	printf("2 - Gerente\n");
	printf("Selecione a categoria (1 ou 2): ");
	scanf("%d", &categoria);

	printf("Digite o número de horas trabalhadas no mês: ");
	scanf("%d", &num_horas);

	/* coeficiente do salario */
	switch (turno) {
	case 1:
		salario_coe = salario_min * 0.10;
	case 2:
		salario_coe = salario_min * 0.15;
	case 3:
		salario_coe = salario_min * 0.12;
	}
	printf("Coeficiente do salário: %.2f\n", salario_coe);

	/* salario bruto (horas * coeficiente) */
	salario_brt = num_horas * salario_coe;
	printf("Salário bruto: %.2f\n", salario_brt);

	/* imposto */
	switch (categoria) {
	case 1:
		if (salario_brt <= 500)
			imposto = salario_brt * 0.03;
		else
			imposto = salario_brt * 0.05;
	case 2:
		if (salario_brt <= 500)
			imposto = salario_brt * 0.04;
		else
			imposto = salario_brt * 0.06;
	}
	printf("Imposto: %.2f", imposto);

	/* gratificação */
	if (turno == 3 && num_horas > 80)
		gratificacao = 50.0;
	else
		gratificacao = 30.0;
	printf("Gratificação: %.2f\n", gratificacao);

	/* auxílio alimentação */
	if (categoria == 1 && salario_coe <= 25)
		aux_alim = salario_brt * (1.0 / 3.0);
	else
		aux_alim = salario_brt / 2.0;
	printf("Auxílio alimentação: %.2f\n", aux_alim);

	/* salário liquido */
	salario_liq = salario_brt - imposto - gratificacao + aux_alim;
	printf("Salário liquído: %.2f\n", salario_liq);

	/* classficicação */
	if (salario_liq < 350.0)
		printf("Classificação: Mal remunerado\n");
	else if (salario_liq >= 350.0 && salario_liq <= 600)
		printf("Classificação: Normal\n");
	else
		printf("Classficação: Bem remunerado\n");

	return (0);
}
