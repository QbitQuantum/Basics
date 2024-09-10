v8::Local<v8::Value> Featureset::NewInstance(mapnik::featureset_ptr fsp)
{
    Nan::EscapableHandleScope scope;
    Featureset* fs = new Featureset();
    fs->this_ = fsp;
    v8::Local<v8::Value> ext = Nan::New<v8::External>(fs);
    Nan::MaybeLocal<v8::Object> maybe_local = Nan::NewInstance(Nan::New(constructor)->GetFunction(), 1, &ext);
    if (maybe_local.IsEmpty()) Nan::ThrowError("Could not create new Featureset instance");
    return scope.Escape(maybe_local.ToLocalChecked());
}