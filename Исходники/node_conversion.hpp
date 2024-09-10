inline optional<v8::Local<v8::Value>> objectMember(v8::Local<v8::Value> value, const char * name) {
    Nan::EscapableHandleScope scope;
    if (!Nan::Has(Nan::To<v8::Object>(value).ToLocalChecked(), Nan::New(name).ToLocalChecked()).FromJust()) {
        return {};
    }
    Nan::MaybeLocal<v8::Value> result = Nan::Get(Nan::To<v8::Object>(value).ToLocalChecked(), Nan::New(name).ToLocalChecked());
    if (result.IsEmpty()) {
        return {};
    }
    return scope.Escape(result.ToLocalChecked());
}