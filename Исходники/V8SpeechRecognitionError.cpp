v8::Handle<v8::Value> V8SpeechRecognitionError::constructorCallback(const v8::Arguments& args)
{
    if (!args.IsConstructCall())
        return throwTypeError("DOM object constructor cannot be called as a function.");

    if (ConstructorMode::current() == ConstructorMode::WrapExistingObject)
        return args.Holder();
    if (args.Length() < 1)
        return throwNotEnoughArgumentsError(args.GetIsolate());

    V8TRYCATCH_FOR_V8STRINGRESOURCE(V8StringResource<>, type, args[0]);
    SpeechRecognitionErrorInit eventInit;
    if (args.Length() >= 2) {
        V8TRYCATCH(Dictionary, options, Dictionary(args[1], args.GetIsolate()));
        if (!fillSpeechRecognitionErrorInit(eventInit, options))
            return v8Undefined();
    }

    RefPtr<SpeechRecognitionError> event = SpeechRecognitionError::create(type, eventInit);

    v8::Handle<v8::Object> wrapper = args.Holder();
    V8DOMWrapper::associateObjectWithWrapper(event.release(), &info, wrapper, args.GetIsolate());
    return wrapper;
}