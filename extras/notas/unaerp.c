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
#include <string.h>


#include "http.h"
#include "unaerp.h"

static const char *
get_credencial(struct json_object *j)
{

	const char 		*cred = NULL;
	struct json_object 	*jcred = NULL;

	json_object_object_get_ex(j, "credencial", &jcred);
	cred = json_object_get_string(jcred);

	return cred;
}

static void
set_header_credencial(struct req *r, const char *cred)
{
	char 		 cheader[1024];
	const char 	*key = "credencial";
	size_t 		 keysz = 0;
	size_t 		 credsz = 0;
	size_t 		 headersz = 0;
	int 		 ret = 0;

	memset(cheader, '\0', sizeof(cheader));

	keysz = strlen(key);
	credsz = strlen(cred);
	headersz = keysz + credsz + 3; /* :<espaco>\'0' */

	ret = snprintf(cheader, headersz , "%s: %s", key, cred);

	if (ret < 0 || ret >= sizeof(cheader))
		return;

	req_add_header(r, cheader);
}

static void
print_boletim(struct json_object *r)
{
	int			 notassz = 0;
	struct json_object	*nota = NULL;
	struct json_object	*notas = NULL;
	struct json_object 	*discp = NULL;
	struct json_object	*nome = NULL;
	struct json_object	*atap = NULL;
	int i;

	json_object_object_get_ex(r, JNOTS, &notas);

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

void
get_boletim(const char *ra, const char *pass)
{
	struct json_object 	*resp_json = NULL;
	struct req 		*r = NULL;
	const char 		*cred = NULL;
	int			 ret = 0;
	char			 fdata[256];

	printf("Boletim: [%s]\n", ra);

	/* init request */
	r = req_init();

	/* create form auth */
	ret = snprintf(fdata, sizeof(fdata), FAUT, ra, pass);
	if (ret < 0 || ret >= sizeof(fdata))
		goto clean;

	/* method post form */
	http_post(r, UAUTH, (const char *)fdata);

	/* requesting.,.*/
	if (r->status_code != 200)
		goto clean;

	resp_json = http_resp_json(r);
	cred = get_credencial(resp_json);
	set_header_credencial(r, cred);

	if (cred == NULL)
		goto clean;

	http_get(r, UBOLE);

	if (r->status_code != 200)
		goto clean;

	if (resp_json != NULL)
		json_object_put(resp_json);

	resp_json = http_resp_json(r);
	print_boletim(resp_json);

clean:
	if (resp_json != NULL)
		json_object_put(resp_json);
	if (r != NULL)
		req_free(r);
}
