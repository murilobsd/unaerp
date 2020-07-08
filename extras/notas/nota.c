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
#define USER "123456"
#define PASS "123456789"
#define FAUT "usuario=%s&senha=%s"

/* urls */
#define UAUTH "https://www3.unaerp.br/aluno/rs/aluno-online"

int
main(int argc, char *argv[])
{
	/* curl */
	CURL 			*curl = NULL;
	CURLcode res;
	/* header list */
	struct curl_slist 	*headers = NULL;
	/* url auth */
	const char 		*url_auth = UAUTH;
	/* data form */
	char 			fdata[256];
	int 			ret;

	/* 'clean' fdata */
	memset(fdata, 0, sizeof(fdata));
	/* inicializa o curl */
	curl = curl_easy_init();
	/* setamos cookkie para memória */
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
	/* adicionamos o user agent */
	curl_easy_setopt(curl, CURLOPT_USERAGENT, HUSE_AGEN);

	/*
	 * Fase 1 GET Autenticação SESSION
	 */

	/* adicionamos os headers */
	headers = curl_slist_append(headers, HSEC_DESD);
	headers = curl_slist_append(headers, HSEC_FETU);
	headers = curl_slist_append(headers, HSEC_MODN);
	headers = curl_slist_append(headers, HSEC_SITE);

	/* adicionamos o header ao request */
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	if (curl) {
		/* adicionamos a url da autenticação */
		curl_easy_setopt(curl, CURLOPT_URL, url_auth);
		/* request */
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl error: %s",
			    curl_easy_strerror(res));
	}

	/*
	 * Fase 2 POST Autenticação
	 */

	/* limpamos o header para adicionar outros */
	headers = NULL;

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
		ret = snprintf(fdata, sizeof(fdata), FAUT, USER, PASS);
		if (ret < 0 || ret >= sizeof(fdata)) {
			fprintf(stderr, "fdata size is big\n");
			goto clean;
		}

		/* adicionamos a url da autenticação */
		curl_easy_setopt(curl, CURLOPT_URL, url_auth);
		/* setamos o tamanho do dos dados do form */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(fdata));
		/* setamos os dados do formulario no request */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fdata);

		/* request */
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl error: %s",
			    curl_easy_strerror(res));
	}

clean:
	/* liberamos a lista ao termino do request */
	curl_slist_free_all(headers);

	/* limpamos o curl */
	curl_easy_cleanup(curl);
	return (0);
}


/*

	struct json_object *json_info;
	struct json_object *json_file = NULL;
	struct json_object *nome;

	CURL curl;
	CURLcode res;

	json_file = json_object_from_file("./resp_auth.json");

	if (json_util_get_last_err() != NULL) {
		printf("Failed parse: %s - %s", json_util_get_last_err(), "resp_auth.json");
		return (1);
	}

	if (json_file == NULL) {
		printf("Failed parse");
		return (1);
	}
	json_object_object_get_ex(json_file, "informacoes", &json_info);

	json_object_object_get_ex(json_info, "nome", &nome);

	printf("Nome: %s\n", json_object_get_string(nome));
*/
