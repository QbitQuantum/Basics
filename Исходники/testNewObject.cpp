static bool
constructHook(JSContext *cx, unsigned argc, jsval *vp)
{
    JS::CallArgs args = CallArgsFromVp(argc, vp);

    // Check that arguments were passed properly from JS_New.

    JS::RootedObject obj(cx, JS_NewObject(cx, js::Jsvalify(&JSObject::class_), JS::NullPtr(), JS::NullPtr()));
    if (!obj) {
        JS_ReportError(cx, "test failed, could not construct object");
        return false;
    }
    if (strcmp(JS_GetClass(obj)->name, "Object") != 0) {
        JS_ReportError(cx, "test failed, wrong class for 'this'");
        return false;
    }
    if (args.length() != 3) {
        JS_ReportError(cx, "test failed, argc == %d", args.length());
        return false;
    }
    if (!args[0].isInt32() || args[2].toInt32() != 2) {
        JS_ReportError(cx, "test failed, wrong value in args[2]");
        return false;
    }
    if (!args.isConstructing()) {
        JS_ReportError(cx, "test failed, not constructing");
        return false;
    }

    // Perform a side-effect to indicate that this hook was actually called.
    JS::RootedValue value(cx, args[0]);
    JS::RootedObject callee(cx, &args.callee());
    if (!JS_SetElement(cx, callee, 0, value))
        return false;

    args.rval().setObject(*obj);

    // trash the argv, perversely
    args[0].setUndefined();
    args[1].setUndefined();
    args[2].setUndefined();

    return true;
}