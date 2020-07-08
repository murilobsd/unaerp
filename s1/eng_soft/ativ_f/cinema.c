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

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

/* Número máximo de assentos da menor sala*/
const int 	 MAX_NUM_ASSENTOS = 40;

/* Número de fileiras */
const int 	 NFIL = 5;

/* Númer de colunas */
const int 	 NCOL = 8;

/* Mensagem da sala em manutenção */
const char 	*MSG_MANUTENCAO = "A sala se encontra em manutenção";

/* status de assento */
enum assento_t {
	LIV,				/* livre */
	OCU,				/* ocupado */
};

static int 	cn_escolha_preco(float *, float *);
static int 	cn_escolha_filme(void);
static void 	cn_init_assentos(enum assento_t *);
static int 	cn_ver_assentos(enum assento_t *);
static int 	cn_res_assentos(enum assento_t *, int *);
static float	cn_fechar_pedido(int, float, float, int *, int *);
static int 	cn_count_assentos(enum assento_t *, enum assento_t);

int
main(int argc, char *argv[])
{
	float 		p_int = 0;		/* preco inteira */
	float 		p_med = 0;		/* preco meia entrada */
	int		filme = 0;		/* opção do filme */
	int		num_assentos = 0;	/* qtd de assentos escolhido */
	int		num_meia = 0;		/* qtd meia entrada */
	int		num_int = 0;		/* qtd inteira entrada */
	float		valor_ingre = 0.0;	/* valor dos ingressos */
	enum assento_t	assentos[NFIL][NCOL];	/* assentos */
	int		num_assen_vagos = 0;	/* num de assentos vagos */
	int		bye = 0;

	cn_init_assentos((enum assento_t *)assentos);


	while (bye == 0) {
		int menu = 0;
		system("clear");

		printf("\n\n************* MENU ******************\n");
		printf("* 1. Definir preço                  *\n");
		printf("* 2. Escolher Filme                 *\n");
		printf("* 3. Reservar assentos              *\n");
		printf("* 4. Fechar pedido                  *\n");
		printf("* 5. Sair                           *\n");
		printf("*************************************\n\n");
		printf("Selecione a opção 1-5: ");
		scanf("%d", &menu);

		switch (menu) {

		case 1:
			printf("**O preço da meia entrada será "
			    "metade do preço da inteira**\n");
			printf("Defina o preço da entrada inteira: ");
			scanf("%f", &p_int);

			if (cn_escolha_preco(&p_int, &p_med) == -1)
				err(1, "cn_escolha_preco");

			printf("Preço Inteira: \t%.2f\n", p_int);
			printf("Preço Meia: \t%.2f\n", p_med);
			break;
		case 2:
			if ((filme = cn_escolha_filme()) == -1)
				err(1, "cn_escolha_filme");
			break;
		case 3:
			if (cn_res_assentos((enum assento_t *)assentos,
			    &num_assentos) == -1)
				err(1, "cn_res_assentos");
			break;
		case 4:
			valor_ingre = cn_fechar_pedido(num_assentos, p_med,
			    p_int, &num_meia, &num_int);

			printf("Valor Total: %.2f\n", valor_ingre);
			break;
		case 5:
			bye = 1;
			break;

		}


	}


	printf("\n\n******* RELATÓRIO *********\n");
	printf("Número de ingressos de meia entrada: %d\n", num_meia);
	printf("Número de ingressos de entrada inteira: %d\n", num_int);
	printf("Número total de ingresso: %d\n", num_meia + num_int);
	printf("Fatura total da sala: %.2f\n", (num_meia * p_med) +
	    (num_int * p_int));

	num_assen_vagos = cn_count_assentos((enum assento_t *)assentos, LIV);
	printf("Número de assentos disponíveis: %d\n", num_assen_vagos);

	printf("\nAté mais ;)\n");

	return (0);
}

static int
cn_count_assentos(enum assento_t *a, enum assento_t a_t)
{
	int f, c;
	int count = 0;

	for (f = 0; f < NFIL; f++)
		for (c = 0; c < NCOL; c++)
			if (*((a+f*NCOL) + c) == a_t)
				count += 1;
	return (count);
}

/*
 * Fecha o pedido das reservas de assentos, retorna o valor a ser
 * cobrado e incremente o número total de ingressos.
 */
static float
cn_fechar_pedido(int num_res, float p_m, float p_i, int *num_m, int *num_i)
{
	int 	count = 0;
	float 	total = 0.0;
	char 	ent_tipo;

	printf("\nForam reservados %d assentos\n", num_res);

	while (count < num_res) {

		printf("Para entrada %d digite m para meia entrada i para"
		    "inteira [m/i]: ", count);
		scanf(" %c", &ent_tipo);

		switch (ent_tipo) {
			case 'm':
				total += p_m;
				*num_m += 1;
				count += 1;
				break;
			case 'i':
				total += p_i;
				*num_i += 1;
				count += 1;
				break;
			default:
				continue;
				break;
		}
	}

	return total;
}

/*
 * Reserva de assentos e a quantidade de número reservados.
 */
static int
cn_res_assentos(enum assento_t *a, int *num_assentos)
{

	int f, c;
	int ret = 0;

	while (1) {

		if (*num_assentos == 40) {
			printf("Lotação máxima\n");
			ret = -1;
			break;
		}

		cn_ver_assentos(a);

		printf("\n\n**Para finalizar digite -1**\n");
		printf("Selecione um dos assentos\n");

		printf("Fileira [1-5]: ");
		scanf("%d", &f);
		if (f == -1)
			break;

		printf("Coluna [1-8]: ");
		scanf("%d", &c);
		if (c == -1)
			break;

		if (f <= 0 || f > 5)
			printf("Fileira inválida: %d\n", f);
		else if (c <= 0 || c > 8)
			printf("Coluna inválida: %d\n", c);
		else {
			--c;
			--f;
			*((a+f*NCOL) + c) = OCU;
			*num_assentos += 1;
		}
	}

	return (ret);
}

/*
 * Exibe a matriz de assentos. O (Ocupado) L (Livre).
 */
static int
cn_ver_assentos(enum assento_t *a)
{
	int f, c;

	printf("*****************************************\n");
	printf("*               TELA                    *\n");
	printf("*****************************************\n\n");
	printf("Legenda:\n");
	printf("L\t=\tLivre\n");
	printf("O\t=\tOcupado\n\n");

	printf("  ");
	for (c = 0; c < NCOL; c++) {
		printf(" %d ", c+1);

		if (c == (NCOL -1))
			printf("\n");
	}
	for (f = 0; f < NFIL; f++) {
		printf("%d ", f + 1);
		for (c = 0; c < NCOL; c++) {
			if (*((a+f*NCOL) + c) == LIV)
				printf(" L ");
			else
				printf(" O ");

			if (c == (NCOL - 1))
				printf("\n");
		}
	}

	return (0);
}

/*
 * Zera os assentos, ou seja, deixa com status livre
 */
static void
cn_init_assentos(enum assento_t *a)
{
	int f, c;

	for (f = 0; f < NFIL; f++)
		for (c = 0; c < NCOL; c++)
			*((a+f*NCOL) + c) = LIV;
}

/*
 * Seleciona o tipo de filme.
 */
static int
cn_escolha_filme(void)
{
	int filme = 0;

	printf("*****************************************\n");
	printf("* 1. Guerra nas Estrelas                *\n");
	printf("* 2. Missão Impossível                  *\n");
	printf("* 3. CasaBlanca                         *\n");
	printf("*****************************************\n");
	printf("Selecione o o filme 1-3: ");
	scanf("%d", &filme);

	if (filme <= 0 || filme > 3) {
		fprintf(stderr, "valor de filme inválido %d\n", filme);
		return (-1);
	}

	return (filme);
}


/*
 * Define os preços dos ingressos.
 */
static int
cn_escolha_preco(float *p_int, float *p_med)
{
	if (p_int == NULL || p_med == NULL) {
		fprintf(stderr, "preços nulos\n");
		return (-1);
	}

	if (*p_int <= 0) {
		fprintf(stderr, "preço inteiro tem que ser positivo\n");
		return (-1);
	}

	*p_med = *p_int / 2.0;

	return (0);
}
