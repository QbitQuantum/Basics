v8::Local<v8::Value> Layer::NewInstance(mapnik::layer const& lay_ref) {
    Nan::EscapableHandleScope scope;
    Layer* l = new Layer();
    // copy new mapnik::layer into the shared_ptr
    l->layer_ = std::make_shared<mapnik::layer>(lay_ref);
    v8::Local<v8::Value> ext = Nan::New<v8::External>(l);
    Nan::MaybeLocal<v8::Object> maybe_local = Nan::NewInstance(Nan::New(constructor)->GetFunction(), 1, &ext);
    if (maybe_local.IsEmpty()) Nan::ThrowError("Could not create new Layer instance");
    return scope.Escape(maybe_local.ToLocalChecked());
}