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
#include <stdlib.h>

/* Número máximo de assentos da menor sala*/
const int 	 MAX_NUM_ASSENTOS = 40;
/* Número de fileiras */
const int 	 NUM_FILEIRA_ASSENTOS = 5;
/* Número de colunas */
const int 	 NUM_COLUNAS_ASSENTOS = 8;
/* Mensagem da sala em manutenção */
const char 	*MSG_MANUTENCAO = "A sala se encontra em manutenção";

int
main(int argc, char *argv[])
{
	/* opção do menu */
	int opcao = 1;
	int valor_saida = 3;

	/* preço do ingresso do tipo inteira e meia */
	float preco_inteira = 0.0;
	float preco_meia = 0.0;

	/* quantidade disponivel de assentos */
	int qtd_disp_asse = MAX_NUM_ASSENTOS;

	/* quantidade de ingressos a serem comprados */
	int qtd_ingressos_comp = 0;

	/* quantidade de tipos de ingresso */
	int qtd_ingresso_meia = 0;
	int qtd_ingresso_inteira = 0;

	/* total de ingressos */
	int 	total_ingr_meia = 0;
	int 	total_ingr_inteira = 0;
	int 	total_vendidos = 0;
	float 	total_valor_vendidos = 0.0;

	while (opcao != 3) {

		printf("MENU\n");
		printf("[1] - Definir preço do ingresso.\n");
		printf("[2] - Venda de Ingressos.\n");
		printf("[3] - Sair.\n");
		printf("Selecione uma das opções do menu [1-3]: ");
		scanf("%d", &opcao);

		if (opcao > 0 && opcao < 4) {
			switch(opcao) {
			case 1:
				printf("Opção 1\n");
				break;
			case 2:
				printf("Opção 1\n");
				break;
			case 3:
				break;
			}
		} else {
			printf("Opção %d é inválida\n", opcao);
			system("clear");
		}

	}

	printf("Defina o valor para o ingresso inteiro: ");
	scanf("%f", &preco_inteira);
	preco_meia = preco_inteira / 2.0;

	/* checagem se o preco e positivo */
	if (preco_inteira <= 0) {
		printf("Preço do ingresso deve ser positivo.\n");
		return (1);
	}

	/* Lista de filmes disponíveis */
	int filme = 1;
	printf("FILMES DISPONÍVEIS\n");
	printf("[1] - Filme 1.\n");
	printf("[2] - Filme 2.\n");
	printf("[3] - Filme 3.\n");
	printf("Selecione uma das opções do menu [1-3]: ");
	scanf("%d", &filme);
	if (filme == 1)
		printf("Filme selecionado: Filme 1\n");
	else if (filme == 2)
		printf("Filme selecionado: Filme 2\n");
	else
		printf("Filme selecionado: Filme 3\n");

	printf("Digite a quantidade de ingressos a serem comprado(s): ");
	scanf("%d", &qtd_ingressos_comp);

	/* checagem quantidade de ingressos positivos */
	if (qtd_ingressos_comp <= 0) {
		printf("Quantidade de ingressos deve ser maior que 0.\n");
		return (1);
	}

	/* checagem quantidade de ingressos não utrapassa a qtd disponível */
	if (qtd_ingressos_comp <= qtd_disp_asse)
		qtd_disp_asse = qtd_disp_asse - qtd_ingressos_comp;
	else {
		printf("Quantidade de ingressos comprados (%d) ultrapassa "
		    "ingressos disponíveis (%d)", qtd_ingressos_comp,
		    qtd_disp_asse);
		return (1);
	}

	printf("Digite a quantidade de ingressos do tipo inteiro: ");
	scanf("%d", &qtd_ingresso_inteira);

	/* checagem se a quantidade de ingressos "inteiros" é maior do que o
	 * selecionado
	 */
	if (qtd_ingresso_inteira > qtd_ingressos_comp) {
		printf("Quantidade de ingressos deve ser menor que a"
		    "quantidade de ingressos comprados.");
		return (1);
	}

	/* checagem automática da quantidade de ingressos */
	if (qtd_ingresso_inteira == 0)
		qtd_ingresso_meia = qtd_ingressos_comp;
	else if (qtd_ingresso_inteira == qtd_ingressos_comp)
		qtd_ingresso_meia = 0;
	else
		qtd_ingresso_meia = qtd_ingressos_comp - qtd_ingresso_inteira;

	printf("\n\n*******************************************************\n");
	printf("Assentos Disponíveis: %d - Total de assentos: %d\n", 1, 1);
	printf("*******************************************************\n\n");

	/* matriz de assentos */
	int assentos[5][8] = {0};

	for (int i = 0; i < qtd_ingressos_comp; i++) {
		int linha = 0;
		int coluna = 0;

		for (int l = 0; l < 5; l++) {
			for (int c = 0; c < 8; c++) {
				if (assentos[l][c] != 0)
					printf("%d\t", 1);
				else
					printf("%d\t", assentos[l][c]);
			}
			printf("\n");
		}

		printf("Selecione a linha [0-4]: ");
		scanf("%d", &linha);

		printf("Selecione a coluna [0-7]: ");
		scanf("%d", &coluna);

		/*
		 * TODO: arrumar depois checagem se a linha é positiva
		 */

		assentos[linha][coluna] = 1;
	}

	/* incremento total de ingressos vendidos para o relatório */
	total_ingr_meia += qtd_ingresso_meia;
	total_ingr_inteira += qtd_ingresso_inteira;
	total_vendidos += total_ingr_meia +  total_ingr_inteira;
	total_valor_vendidos += (total_ingr_meia * preco_meia) +
	    (total_ingr_inteira + preco_inteira);

	/* instruções para o relatório */
	printf("Número de ingressos inteiros: %d\n", total_ingr_inteira);
	printf("Número de ingressos meia: %d\n", total_ingr_meia);
	printf("Número de ingressos vendidos: %d\n", total_vendidos);
	printf("Valor total de ingressos vendidos: %.2f\n", total_valor_vendidos);
	printf("Número de lugares não ocupados: %d\n", qtd_disp_asse);

	return (0);
}
