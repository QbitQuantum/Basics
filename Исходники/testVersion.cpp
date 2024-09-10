JSBool
EvalScriptVersion16(JSContext *cx, uintN argc, jsval *vp)
{
    JS_ASSERT(argc == 1);
    jsval *argv = JS_ARGV(cx, vp);
    JS_ASSERT(JSVAL_IS_STRING(argv[0]));
    JSString *str = JSVAL_TO_STRING(argv[0]);
    const jschar *chars = str->getChars(cx);
    JS_ASSERT(chars);
    size_t len = str->length();
    return callbackData->evalVersion(chars, len, JSVERSION_1_6);
}