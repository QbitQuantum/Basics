/*	HTTPMakeResponse
**	----------------
**	Makes a HTTP/1.0-1.1 response header.
*/
PRIVATE int HTTPMakeResponse (HTStream * me, HTRequest * request)
{
    char crlf[3];
    HTRsHd response_mask = HTRequest_rsHd(request);
    *crlf = CR; *(crlf+1) = LF; *(crlf+2) = '\0';

    if (response_mask & HT_S_LOCATION) {		/* @@@ */

    }
    if (response_mask & HT_S_PROXY_AUTH) {		/* @@@ */

    }
    if (response_mask & HT_S_PUBLIC) {			/* @@@ */

    }
    if (response_mask & HT_S_RETRY_AFTER) {		/* @@@ */

    }
    if (response_mask & HT_S_SERVER) {
	PUTS("Server: ");
	PUTS(HTLib_appName());
	PUTC('/');
	PUTS(HTLib_appVersion());
	PUTC(' ');
	PUTS(HTLib_name());
	PUTC('/');
	PUTS(HTLib_version());
	PUTBLOCK(crlf, 2);
    }
    if (response_mask & HT_S_WWW_AUTH) {		/* @@@ */

    }
    HTTRACE(PROT_TRACE, "HTTP........ Generating Response Headers\n");
    return HT_OK;
}