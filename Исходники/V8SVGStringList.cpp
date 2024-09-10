static v8::Handle<v8::Value> initializeCallback(const v8::Arguments& args)
{
    if (args.Length() < 1)
        return throwNotEnoughArgumentsError(args.GetIsolate());
    RefPtr<SVGStaticListPropertyTearOff<SVGStringList> > imp = V8SVGStringList::toNative(args.Holder());
    ExceptionCode ec = 0;
    {
    V8TRYCATCH_FOR_V8STRINGRESOURCE(V8StringResource<>, item, MAYBE_MISSING_PARAMETER(args, 0, DefaultIsUndefined));
    String result = imp->initialize(item, ec);
    if (UNLIKELY(ec))
        goto fail;
    return v8String(result, args.GetIsolate());
    }
    fail:
    return setDOMException(ec, args.GetIsolate());
}