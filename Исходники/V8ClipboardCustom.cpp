v8::Handle<v8::Value> V8Clipboard::getDataCallback(const v8::Arguments& args)
{
    INC_STATS("DOM.Clipboard.getData()");
    Clipboard* clipboard = V8Clipboard::toNative(args.Holder());

    if (args.Length() != 1)
        return throwError("getData: Invalid number of arguments", V8Proxy::SyntaxError);

    bool success;
    String result = clipboard->getData(toWebCoreString(args[0]), success);
    if (success)
        return v8String(result);

    return v8::Undefined();
}