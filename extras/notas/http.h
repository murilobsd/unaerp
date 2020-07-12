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

#include <curl/curl.h>

enum http_method {
	GET,
	POST
};

struct res {
	char	*content;
	size_t	 size;
};

struct req {
	CURLcode 	 	 res;
	enum http_method	 method;
	CURL 		 	*curl;
	char			*url;
	char			*data;
	size_t			 datasz;
	struct curl_slist	*headers;
	int			 timeout;
	long	 		 status_code;
	struct res		resp;
};

struct req 	*req_init(void);
int		 req_set_url(struct req *, const char *, size_t);
int		 req_set_method(struct req *, enum http_method);
int		 req_add_header(struct req *, const char *);
int		 req_set_data(struct req *, const char *);
void		 req_do(struct req *);
void		 req_free(struct req *);
