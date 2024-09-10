static v8::Handle<v8::Value> removeSourceBufferCallback(const v8::Arguments& args)
{
    if (args.Length() < 1)
        return throwNotEnoughArgumentsError(args.GetIsolate());
    MediaSource* imp = V8MediaSource::toNative(args.Holder());
    ExceptionCode ec = 0;
    {
    V8TRYCATCH(SourceBuffer*, buffer, V8SourceBuffer::HasInstance(MAYBE_MISSING_PARAMETER(args, 0, DefaultIsUndefined)) ? V8SourceBuffer::toNative(v8::Handle<v8::Object>::Cast(MAYBE_MISSING_PARAMETER(args, 0, DefaultIsUndefined))) : 0);
    imp->removeSourceBuffer(buffer, ec);
    if (UNLIKELY(ec))
        goto fail;
    return v8Undefined();
    }
    fail:
    return setDOMException(ec, args.GetIsolate());
}