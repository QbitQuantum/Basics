static JSBool
Exception(JSContext *cx, uintN argc, Value *vp)
{
    CallArgs args = CallArgsFromVp(argc, vp);

    /*
     * ECMA ed. 3, 15.11.1 requires Error, etc., to construct even when
     * called as functions, without operator new.  But as we do not give
     * each constructor a distinct JSClass, whose .name member is used by
     * NewNativeClassInstance to find the class prototype, we must get the
     * class prototype ourselves.
     */
    Value protov;
    if (!args.callee().getProperty(cx, cx->runtime->atomState.classPrototypeAtom, &protov))
        return false;

    if (!protov.isObject()) {
        JS_ReportErrorNumber(cx, js_GetErrorMessage, NULL, JSMSG_BAD_PROTOTYPE, "Error");
        return false;
    }

    JSObject *errProto = &protov.toObject();
    JSObject *obj = NewNativeClassInstance(cx, &ErrorClass, errProto, errProto->getParent());
    if (!obj)
        return false;

    /* Set the 'message' property. */
    JSString *message;
    if (args.length() != 0 && !args[0].isUndefined()) {
        message = js_ValueToString(cx, args[0]);
        if (!message)
            return false;
        args[0].setString(message);
    } else {
        message = NULL;
    }

    /* Find the scripted caller. */
    FrameRegsIter iter(cx);
    while (!iter.done() && !iter.fp()->isScriptFrame())
        ++iter;

    /* Set the 'fileName' property. */
    JSString *filename;
    if (args.length() > 1) {
        filename = js_ValueToString(cx, args[1]);
        if (!filename)
            return false;
        args[1].setString(filename);
    } else {
        if (!iter.done()) {
            filename = FilenameToString(cx, iter.fp()->script()->filename);
            if (!filename)
                return false;
        } else {
            filename = cx->runtime->emptyString;
        }
    }

    /* Set the 'lineNumber' property. */
    uint32_t lineno;
    if (args.length() > 2) {
        if (!ValueToECMAUint32(cx, args[2], &lineno))
            return false;
    } else {
        lineno = iter.done() ? 0 : js_FramePCToLineNumber(cx, iter.fp(), iter.pc());
    }

    intN exnType = args.callee().getReservedSlot(JSSLOT_ERROR_EXNTYPE).toInt32();
    if (!InitExnPrivate(cx, obj, message, filename, lineno, NULL, exnType))
        return false;

    args.rval().setObject(*obj);
    return true;
}