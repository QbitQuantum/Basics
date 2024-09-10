static JSBool
AfxGlobal_soundRecStart(JSContext *cx, unsigned argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	if(2 > args.length())
		return JS_FALSE;

	double volume;

	if(!JS::ToNumber(cx, args[1], &volume))
		return JS_FALSE;

    JSString *str = JS_ValueToString(cx, args[0]);
    if (!str)
        return JS_FALSE;

    char *c_str = JS_EncodeString(cx, str);
	if(!c_str)
		return JS_FALSE;

	std::wstring wPath;

	if(!AnsiStringToWideString(c_str, wPath))
	{
		JS_free(cx, c_str);
		return JS_FALSE;
	}

	JS_free(cx, c_str);

	bool result = g_Filming.GetFilmSound()->Start(wPath.c_str(), 0, (float)volume);

	args.rval().set(BOOLEAN_TO_JSVAL(result));
    return JS_TRUE;
}