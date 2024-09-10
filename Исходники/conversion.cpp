v8::Local<v8::Function> Convert::getCallbackFunction(v8::Local<v8::Value> js)
{
    Nan::EscapableHandleScope scope;
    if (!js->IsFunction())
    {
        throw std::runtime_error("function");
    }
    return scope.Escape(js.As<v8::Function>());
}