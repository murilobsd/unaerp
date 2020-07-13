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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "http.h"

static const char *method_str[] = {
	"GET",
	"POST",
};

static const char 	*get_meth(enum http_method);
static size_t		 recv_cb(char *, size_t, size_t, void *);

void
http_do(struct req *r)
{
	struct res  resp;
	const char *m = get_meth(r->method);

	if (r->resp.content != NULL)
		free(r->resp.content);

	r->resp.content = NULL;
	r->resp.size = 0;

	if (r == NULL) {
		printf("req_set_url req is null\n");
		return;
	}


	//curl_easy_setopt(r->curl, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(r->curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(r->curl, CURLOPT_COOKIEFILE, "");
	curl_easy_setopt(r->curl, CURLOPT_URL, (const char *)r->url);
	curl_easy_setopt(r->curl, CURLOPT_HTTPHEADER, r->headers);
	curl_easy_setopt(r->curl, CURLOPT_WRITEFUNCTION, recv_cb);
	curl_easy_setopt(r->curl, CURLOPT_WRITEDATA, (void *)r);

	switch (r->method) {
	case GET:
		curl_easy_setopt(r->curl, CURLOPT_HTTPGET, 1L);
		break;
	case POST:
		curl_easy_setopt(r->curl, CURLOPT_POST, 1L);
		curl_easy_setopt(r->curl, CURLOPT_POSTFIELDSIZE, r->datasz);
		curl_easy_setopt(r->curl, CURLOPT_POSTFIELDS, r->data);
		break;
	default:
		break;
	}

	r->res = curl_easy_perform(r->curl);
	if (r->res != CURLE_OK) {
		printf("http_do: %s\n", curl_easy_strerror(r->res));
		r->status_code = 500;
		return;
	}
	curl_easy_getinfo(r->curl, CURLINFO_RESPONSE_CODE, &r->status_code);

	printf("[%s] - %s - %lu\n", m, r->url, r->status_code);
}

int
http_post(struct req *r, const char *u, const char *d)
{
	req_set_url(r, u, strlen(u));
	req_set_method(r, POST);
	req_set_data(r, d);
	http_do(r);

	return (0);
}

struct json_object *
http_resp_json(struct req *r)
{
	struct json_object *j = NULL;

	if (r == NULL) {
		printf("req_set_method req is null\n");
		return NULL;
	}
	if (r->resp.content == NULL) {
		printf("http_resp_json resp is null\n");
		return NULL;
	}

	j = json_tokener_parse(r->resp.content);

	return j;
}


int
http_get(struct req *r, const char *u)
{
	req_set_url(r, u, strlen(u));
	req_set_method(r, GET);
	http_do(r);

	return (0);
}

int
req_set_data(struct req *r, const char *d)
{
	size_t datasz = 0;

	if (r == NULL) {
		printf("req_set_data req is null\n");
		return (1);
	}

	datasz = strlen(d);

	if (r->data != NULL)
		free(r->data);

	r->data = (char *)malloc(datasz + 1);
	r->datasz = datasz;

	memset(r->data, '\0', datasz + 1);
	memcpy(r->data, d, datasz);

	return (0);
}

int
req_add_header(struct req *r, const char *h)
{
	if (r == NULL) {
		printf("req_set_method req is null\n");
		return (1);
	}
	r->headers = curl_slist_append(r->headers, h);
	return (0);
}

int
req_set_method(struct req *r, enum http_method m)
{
	if (r == NULL) {
		printf("req_set_method req is null\n");
		return (1);
	}
	r->method = m;

	return (0);
}

int
req_set_url(struct req *r, const char *u, size_t sz)
{
	int res = 0;

	if (r == NULL) {
		printf("req_set_url req is null\n");
		goto clean;
	}

	r->url = strndup(u, sz);
	if (r->url == NULL) {
		printf("req_set_url strdup\n");
		goto clean;
	}

	return (0);
clean:
	if (r->url != NULL) free(r->url);
	return (1);
}

struct req *
req_init(void)
{
	struct req *r = NULL;

	r = (struct req *)calloc(1, sizeof(struct req));
	if (r == NULL) {
		printf("req_init alloc failed\n");
		return NULL;
	}

	curl_global_init(CURL_GLOBAL_ALL);
	r->curl = curl_easy_init();
	if (r->curl == NULL) {
		printf("rw_init curl failed\n");
		req_free(r);
		return NULL;
	}


	r->method = GET;
	r->headers = NULL;
	r->data = NULL;
	r->datasz = 0;
	r->status_code = 0;
	r->resp.content = NULL;
	r->resp.size = 0;
	r->timeout = 20;

	return (r);
}

void
req_free(struct req *r)
{
	if (r->url != NULL)
		free(r->url);
	if (r->resp.content != NULL)
		free(r->resp.content);
	if (r->headers != NULL)
		curl_slist_free_all(r->headers);
	if (r->curl != NULL) {
		curl_easy_cleanup(r->curl);
		curl_global_cleanup();
	}
	if (r->data != NULL)
		free(r->data);
	if (r != NULL)
		free(r);

	r->url = NULL;
	r->headers = NULL;
	r->resp.content = NULL;
	r->resp.size = 0;
}

static const char *
get_meth(enum http_method m)
{
	return method_str[m];
}

static size_t
recv_cb(char *ptr, size_t size, size_t nmemb, void *data)
{
	struct req *pr = (struct req *)data;
	size_t ptrsize = nmemb * size;
	size_t resize = pr->resp.size + ptrsize + 1;

	pr->resp.content = realloc(pr->resp.content, resize);

	if (pr->resp.content == NULL){
		fprintf(stderr, "recv_data_callback: realloc failed\n");
		return (0);
	}
	memcpy(&(pr->resp.content[pr->resp.size]), ptr, ptrsize);
	pr->resp.size += ptrsize;
	pr->resp.content[pr->resp.size] = '\0';

 	return ptrsize;
}
