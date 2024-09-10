int Printf (const char *msg, ...)
{
	static char s[512];
	int ret=0;
	va_list ap;
	va_start(ap,msg);
	ret=vsprintf_s(s, sizeof(s), msg, ap);
	va_end(ap);
	AvpCallback(AVP_CALLBACK_PUT_STRING,(DWORD)s);
	return ret;
}