inline v8::Local<v8::Value> node::Function::callback(v8::Isolate* isolate, const v8::Local<v8::Function> &function, const v8::Local<v8::Object> &this_object, size_t argc, const v8::Local<v8::Value> arguments[]) {
    Nan::TryCatch trycatch;
    
    auto recv = this_object.IsEmpty() ? isolate->GetCurrentContext()->Global() : this_object;
    auto result = Nan::MakeCallback(recv, function, (int)argc, const_cast<v8::Local<v8::Value>*>(arguments));

    if (trycatch.HasCaught()) {
        throw node::Exception(isolate, trycatch.Exception());
    }
    return result;
}