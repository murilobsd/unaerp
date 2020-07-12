#include <stdio.h>
#include <string.h>

#include "http.h"

int
main(int argc, char *argv[])
{
	struct req 	*r = NULL;
	const char 	*url = "https://httpbin.org/get";
	size_t 		 urlsz = strlen(url) + 2;

	r = req_init();

	req_set_url(r, "https://httpbin.org/get", urlsz);
	req_set_method(r, GET);
	req_add_header(r, "X-UserAgent: unaerp/0.1");
	//http_add_params(r, "Accept: application/json;");
	//http_add_data(r, "Accept: application/json;");

	req_do(r);
	if (r->status_code == 200) {
		printf("Response: %s\n", r->resp.content);
	}
	req_free(r);

	return (0);
}
