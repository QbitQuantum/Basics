static AuBool
nas_error_handler(AuServer* aud, AuErrorEvent* ev)
{
	char s[100];
	AuGetErrorText(aud, ev->error_code, s, 100);
	NAS_CRITICAL("error [%s]\n"
		     "error_code: %d\n"
		     "request_code: %d\n"
		     "minor_code: %d\n",
		     s, ev->error_code, ev->request_code, ev->minor_code);

	LONGJMP(nas_server_sig, 1);
	return AuTrue;
}