v8::Local<v8::Object> toJS(const Properties& properties) {
    Nan::EscapableHandleScope scope;

    v8::Local<v8::Object> result = Nan::New<v8::Object>();
    for (const auto& property : properties) {
        Nan::Set(result, Nan::New(property.first).ToLocalChecked(), toJS(property.second));
    }

    return scope.Escape(result);
}