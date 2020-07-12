#include <stdio.h>
#include <string.h>

#include "http.h"

int
main(int argc, char *argv[])
{
	struct req 	*r = NULL;
	const char 	*urlg = "https://httpbin.org/get";
	const char 	*urlp = "http://httpbin.org/post";
	const char	*dataform = "usuario=teste&senha=teste";
	size_t 		 urlgsz = strlen(urlg);
	size_t 		 urlpsz = strlen(urlp);

	/* init request */
	r = req_init();

	/* method get  */
	/* req_set_url(r, "https://httpbin.org/get", urlg); */
	/* req_set_method(r, GET); */

	/* method post form */
	req_set_url(r, urlp, urlpsz);
	req_set_method(r, POST);
	req_set_data(r, dataform);

	/* add header */
	req_add_header(r, "X-UserAgent: unaerp/0.1");

	//http_add_params(r, "Accept: application/json;");
	//http_add_data(r, "Accept: application/json;");

	/* requesting.,.*/
	req_do(r);
	if (r->status_code == 200) {
		printf("Response: %s\n", r->resp.content);
	}
	req_free(r);

	return (0);
}
