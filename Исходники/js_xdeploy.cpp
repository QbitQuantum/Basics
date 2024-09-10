JSBool netgetjoinableous(JSContext * cx, JSObject * obj, uintN argc, jsval * argv, jsval * rval)
{
	LPWSTR domain, account, password;
	JS_BeginRequest(cx);
	if(!JS_ConvertArguments(cx, argc, argv, "W W W", &domain, &account, &password))
	{
		JS_ReportError(cx, "Error parsing arguments in NetGetJoinableOUs");
		JS_EndRequest(cx);
	}

	JS_YieldRequest(cx);
	DWORD ouCount = 0;
	LPWSTR * ous = NULL;
	DWORD status = NetGetJoinableOUs(NULL, domain, (JSVAL_IS_NULL(argv[1]) ? NULL : account), (JSVAL_IS_NULL(argv[2]) ? NULL : password), &ouCount, &ous);
	if(status != NERR_Success)
	{
		JS_NewNumberValue(cx, status, rval);
		JS_EndRequest(cx);
		return JS_TRUE;
	}

	JSObject * arrayObj = JS_NewArrayObject(cx, 0, NULL);
	*rval = OBJECT_TO_JSVAL(arrayObj);
	for(DWORD i = 0; i < ouCount; i++)
	{
		JSString * curOu = JS_NewUCStringCopyZ(cx, (jschar*)ous[i]);
		JS_DefineElement(cx, arrayObj, i, STRING_TO_JSVAL(curOu), NULL, NULL, 0);
	}
	NetApiBufferFree(ous);
	JS_EndRequest(cx);
	return JS_TRUE;
}