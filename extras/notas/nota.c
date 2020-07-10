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
#include <string.h>

#include <curl/curl.h>
#include <json-c/json.h>

/* Sec headers */
#define HSEC_DESD "document"
#define HSEC_DESE "empty"
#define HSEC_MODC "cors"
#define HSEC_MODN "navigate"
#define HSEC_SITE "same-origin"
#define HSEC_FETU "?1"

/* Outros headers */
#define HEAD_CRED "null"
#define HEAD_ORIG "https://www3.unaerp.br"
#define HEAD_REFE "https://www3.unaerp.br/aluno/"
#define HEAD_XREQ "XMLHttpRequest"
#define HUSE_AGEN "Mozilla/5.0 (X11; OpenBSD amd64; Linux x86_64) "\
	"AppleWebKit/537.36(KHTML, like Gecko) Chrome/83.0.4103.116"\
        "Safari/537.36"

/* usuario e senha */
#ifdef RA
#define USER RA
#define PASS RAS
#else
#define USER "usuario"
#define PASS "senha"
#endif


/* cados de formulario */
#define FAUT "usuario=%s&senha=%s"
#define FRET "modulo=apresentacao&credencial=%s"

/* urls */
#define UAUTH "https://www3.unaerp.br/aluno/rs/aluno-online"
#define UREGI "https://www3.unaerp.br/aluno/rs/aluno-online/registrar-acesso"

/* json key */
#define JAVPA "avaliacaoParcial"
#define JAVFI "avaliacaoFinal"
#define JCRED "credencial"
#define JDISC "disciplina"
#define JNOME "nome"
#define JNOTS "notas"

static int 	un_init_nota(CURL *, struct curl_slist *, const char *);
static int 	un_auth_nota(CURL *, struct curl_slist *, const char *,
    const char *, const char *);
static int 	get_credentials(const char *, char **, size_t *);
static int	get_boletim(const char *);

int
main(int argc, char *argv[])
{
	CURL 			*curl = NULL;
	struct curl_slist 	*headers = NULL;	/* header list */
	const char 		*url = UAUTH; 		/* url auth */
	int 			ret = 0;
	char			*cred = NULL;		/* token */
	size_t			credsz = 0;		/* token size */

	/* inicializa o curl */
	curl = curl_easy_init();

	/*
	 * Fase 1 GET Autenticação SESSION
	if ((ret = un_init_nota(curl, headers, url)) != 0)
		goto clean;
	 */

	/*
	 * Fase 2 POST Autenticação
	headers = NULL;
	if ((ret = un_auth_nota(curl, headers, url, USER, PASS)) != 0)
		goto clean;
	 */

	/* Obtenho a credencial de autenticação */
	if ((ret = get_credentials("./resp_auth.json", &cred, &credsz)) != 0)
		goto clean;
	
	/* printf("Credencial: %s Tamanho: %lu\n", cred, credsz); */

	/* TODO: Registrar o acesso */

	/* TODO: Obter Boletim */

	/* Parsear dados do boletim */
	if ((ret = get_boletim("./resp_nota.json")) != 0)
		goto clean;

clean:

	/* limpaoas as crdenciais */
	if (cred != NULL) free(cred);

	/* liberamos a lista ao termino do request */
	curl_slist_free_all(headers);

	/* limpamos o curl */
	curl_easy_cleanup(curl);
	return (ret);
}

/*
 * Get boletim.
 */
static int
get_boletim(const char *from)
{
	int 			 ret = 0;
	int			 notassz = 0;
	struct json_object 	*base = NULL;
	struct json_object	*nota = NULL;
	struct json_object	*notas = NULL;
	struct json_object 	*discp = NULL;
	struct json_object	*nome = NULL;
	struct json_object	*atap = NULL;
	int i;

	base = json_object_from_file(from);

	if (json_util_get_last_err() != NULL) {
		printf("Failed parse: %s - %s", json_util_get_last_err(),
		    "resp_note.json");
		ret = 1;
	} else if (base == NULL) {
		printf("Failed parse");
		ret = 1;	
	} else {
		json_object_object_get_ex(base, JNOTS, &notas);

		/* tamanho do array notas */
		notassz = json_object_array_length(notas);

		for (i = 0; i < notassz; i++) {
			nota = json_object_array_get_idx(notas, i);
			json_object_object_get_ex(nota, JDISC, &discp);
			json_object_object_get_ex(discp, JNOME, &nome);
			json_object_object_get_ex(nota, JAVPA, &atap);

			printf("Disciplina: %s Atividade Parcial: %s\n",
			    json_object_get_string(nome),
			    json_object_get_string(atap));
		}

	}

	if (base != NULL)
		json_object_put(base);

	return (ret);
}

/*
 * Retorna o token obtido na autenticação, esse token tem que ser usado
 * nos próximos requests.
 */
static int
get_credentials(const char *from, char **to, size_t *tosz)
{
	int 			 ret = 0;
	size_t			 credsz = 0;
	struct json_object 	*base = NULL;
	struct json_object 	*cred = NULL;

	base = json_object_from_file(from);

	if (json_util_get_last_err() != NULL) {
		printf("Failed parse: %s - %s", json_util_get_last_err(),
		    "resp_auth.json");
		ret = 1;
	} else if (base == NULL) {
		printf("Failed parse");
		ret = 1;	
	} else {
		json_object_object_get_ex(base, JCRED, &cred);

		const char *cred_str = json_object_get_string(cred);
		credsz = strlen(cred_str);

		if (credsz <= 0) {
			printf("Credencial não encontradas: %s\n", from);
			ret = 1;
		} else {
			*to = (char *)malloc(credsz + 2);
			if (*to == NULL) {
				printf("Failed malloc credentials\n");
				ret = 1;
			} else {
				*tosz = credsz + 1;
				if(strlcpy(*to, cred_str, credsz+1) >= credsz + 2) {
					printf("buffer pequeno\n");
					ret = 1;
				}
			}
		}
	}

	if (base != NULL)
		json_object_put(base);

	return (ret);
}

/*
 * Método que realiza a autenticação no sistema do Aluno Online
 */
static int
un_auth_nota(CURL *curl, struct curl_slist *headers, const char *url,
    const char *ra, const char *passwd)
{
	char 		fdata[256];
	int 		ret = 0;
	CURLcode 	res;

	/* 'clean' fdata */
	memset(fdata, 0, sizeof(fdata));

	headers = curl_slist_append(headers, HEAD_CRED);
	headers = curl_slist_append(headers, HEAD_ORIG);
	headers = curl_slist_append(headers, HEAD_REFE);
	headers = curl_slist_append(headers, HEAD_XREQ);
	headers = curl_slist_append(headers, HSEC_DESE);
	headers = curl_slist_append(headers, HSEC_FETU);
	headers = curl_slist_append(headers, HSEC_MODC);
	headers = curl_slist_append(headers, HSEC_SITE);

	/* adicionamos o header ao request */
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	/* segundo post enviando dados de formulário */
	if (curl) {
		/* TODO: encodar os dados */
		/* criamos os dados a serem submetidos */
		ret = snprintf(fdata, sizeof(fdata), FAUT, ra, passwd);
		if (ret < 0 || ret >= sizeof(fdata)) {
			fprintf(stderr, "fdata size is big\n");
			ret = 1;
		}

		/* adicionamos a url da autenticação */
		curl_easy_setopt(curl, CURLOPT_URL, url);
		/* setamos o tamanho do dos dados do form */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(fdata));
		/* setamos os dados do formulario no request */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fdata);

		/* request */
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			fprintf(stderr, "curl error: %s",
			    curl_easy_strerror(res));
			ret = 1;
		}
	}

	return (ret);
}

/*
 * Somente realiza um request GET para obter os cookies que serão usados
 * no decorret de outros requests.
 */
static int
un_init_nota(CURL *curl, struct curl_slist *headers, const char *url)
{
	CURLcode 	res;
	int 		ret = 0;

	/* setamos cookkie para memória */
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
	/* adicionamos o user agent */
	curl_easy_setopt(curl, CURLOPT_USERAGENT, HUSE_AGEN);

	/* adicionamos os headers */
	headers = curl_slist_append(headers, HSEC_DESD);
	headers = curl_slist_append(headers, HSEC_FETU);
	headers = curl_slist_append(headers, HSEC_MODN);
	headers = curl_slist_append(headers, HSEC_SITE);

	/* adicionamos o header ao request */
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	if (curl) {
		/* adicionamos a url da autenticação */
		curl_easy_setopt(curl, CURLOPT_URL, url);
		/* request */
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			fprintf(stderr, "curl error: %s",
			    curl_easy_strerror(res));
			ret = 1;
		}
	}

	return (ret);

}
