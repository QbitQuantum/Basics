int callback_uri(http_parser *parser, const char *pos, size_t len)

{

	http_message *message = (http_message *) TlsGetValue(dwTlsIndex);

	char uri_buf[MAX_URI_SIZE];

	DWORD uri_buflen = MAX_URI_SIZE;

	

	strncpy_s(uri_buf, MAX_URI_SIZE, pos, len);

	InternetCanonicalizeUrlA(uri_buf, message->request_uri, &uri_buflen, ICU_DECODE | ICU_NO_ENCODE);



	return 0;

}