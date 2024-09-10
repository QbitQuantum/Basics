v8::Handle<v8::Value> V8InjectedScriptHost::evaluateCallback(const v8::Arguments& args)
{
    INC_STATS("InjectedScriptHost.evaluate()");
    if (args.Length() < 1)
        return v8::ThrowException(v8::Exception::Error(v8::String::New("One argument expected.")));

    v8::Handle<v8::String> expression = args[0]->ToString();
    if (expression.IsEmpty())
        return v8::ThrowException(v8::Exception::Error(v8::String::New("The argument must be a string.")));

    v8::Handle<v8::Script> script = v8::Script::Compile(expression);
    if (script.IsEmpty()) // Return immediately in case of exception to let the caller handle it.
        return v8::Handle<v8::Value>();
    return script->Run();
}