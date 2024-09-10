v8::Handle<v8::Value> V8WorkerContext::importScriptsCallback(const v8::Arguments& args)
{
    INC_STATS("DOM.WorkerContext.importScripts()");
    if (!args.Length())
        return v8::Undefined();

    Vector<String> urls;
    for (int i = 0; i < args.Length(); i++) {
        V8TRYCATCH(v8::Handle<v8::String>, scriptUrl, args[i]->ToString());
        if (scriptUrl.IsEmpty())
            return v8::Undefined();
        urls.append(toWebCoreString(scriptUrl));
    }

    WorkerContext* workerContext = V8WorkerContext::toNative(args.Holder());

    ExceptionCode ec = 0;
    workerContext->importScripts(urls, ec);

    if (ec)
        return setDOMException(ec, args.GetIsolate());

    return v8::Undefined();
}