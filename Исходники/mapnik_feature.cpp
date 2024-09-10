v8::Local<v8::Value> Feature::NewInstance(mapnik::feature_ptr f_ptr)
{
    Nan::EscapableHandleScope scope;
    Feature* f = new Feature(f_ptr);
    v8::Local<v8::Value> ext = Nan::New<v8::External>(f);
    return scope.Escape(Nan::New(constructor)->GetFunction()->NewInstance(1, &ext));
}