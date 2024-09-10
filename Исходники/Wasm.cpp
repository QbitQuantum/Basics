static bool
WasmTextToBinary(JSContext* cx, unsigned argc, Value* vp)
{
    CallArgs args = CallArgsFromVp(argc, vp);
    RootedObject callee(cx, &args.callee());

    if (args.length() != 1) {
        ReportUsageError(cx, callee, "Wrong number of arguments");
        return false;
    }

    if (!args[0].isString()) {
        ReportUsageError(cx, callee, "First argument must be a String");
        return false;
    }

    AutoStableStringChars twoByteChars(cx);
    if (!twoByteChars.initTwoByte(cx, args[0].toString()))
        return false;

    UniqueChars error;
    wasm::UniqueBytecode bytes = wasm::TextToBinary(twoByteChars.twoByteChars(), &error);
    if (!bytes) {
        JS_ReportErrorNumber(cx, GetErrorMessage, nullptr, JSMSG_WASM_TEXT_FAIL,
                             error.get() ? error.get() : "out of memory");
        return false;
    }

    Rooted<ArrayBufferObject*> buffer(cx, ArrayBufferObject::create(cx, bytes->length()));
    if (!buffer)
        return false;

    memcpy(buffer->dataPointer(), bytes->begin(), bytes->length());

    args.rval().setObject(*buffer);
    return true;
}