v8::Local<v8::Value> Color::NewInstance(mapnik::color const& color) {
    Nan::EscapableHandleScope scope;
    Color* c = new Color();
    c->this_ = std::make_shared<mapnik::color>(color);
    v8::Local<v8::Value> ext = Nan::New<v8::External>(c);
    Nan::MaybeLocal<v8::Object> maybe_local = Nan::NewInstance(Nan::New(constructor)->GetFunction(), 1, &ext);
    if (maybe_local.IsEmpty()) Nan::ThrowError("Could not create new Color instance");
    return scope.Escape(maybe_local.ToLocalChecked());
}