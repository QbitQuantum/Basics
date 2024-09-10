static bool
InternalConst(JSContext *cx, unsigned argc, jsval *vp)
{
    CallArgs args = CallArgsFromVp(argc, vp);
    if (args.length() == 0) {
        JS_ReportError(cx, "the function takes exactly one argument");
        return false;
    }

    JSString *str = ToString(cx, args[0]);
    if (!str)
        return false;
    JSFlatString *flat = JS_FlattenString(cx, str);
    if (!flat)
        return false;

    if (JS_FlatStringEqualsAscii(flat, "INCREMENTAL_MARK_STACK_BASE_CAPACITY")) {
        vp[0] = UINT_TO_JSVAL(js::INCREMENTAL_MARK_STACK_BASE_CAPACITY);
    } else {
        JS_ReportError(cx, "unknown const name");
        return false;
    }
    return true;
}