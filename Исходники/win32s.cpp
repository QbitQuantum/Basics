JSBool win32_impersonateuser(JSContext * cx, JSObject * obj, uintN argc, jsval * argv, jsval * rval)
{
	JSString * username, * password, *domain = NULL;
	DWORD logonType = LOGON32_LOGON_INTERACTIVE;
	JS_BeginRequest(cx);
	if(!JS_ConvertArguments(cx, argc, argv, "S S /S u", &username, &password, &domain, &logonType))
	{
		JS_ReportError(cx, "Unable to parse arguments in ImpersonateUser");
		JS_EndRequest(cx);
		return JS_FALSE;
	}

	if(logonType == LOGON32_LOGON_NETWORK)
	{
		*rval = JSVAL_FALSE;
		JS_EndRequest(cx);
		return JS_TRUE;
	}

	LPWSTR domainName = NULL;
	if(domain != NULL)
		domainName = (LPWSTR)JS_GetStringChars(domain);

	HANDLE newToken = NULL;
	JS_YieldRequest(cx);
	if(!LogonUser((LPWSTR)JS_GetStringChars(username), domainName, (LPWSTR)JS_GetStringChars(password), logonType, LOGON32_PROVIDER_DEFAULT, &newToken))
	{
		*rval = JSVAL_FALSE;
		JS_EndRequest(cx);
		return JS_TRUE;
	}

	if(!ImpersonateLoggedOnUser(newToken))
		*rval = JSVAL_FALSE;
	else
		*rval = JSVAL_TRUE;
	CloseHandle(newToken);
	JS_EndRequest(cx);
	return JS_TRUE;
}