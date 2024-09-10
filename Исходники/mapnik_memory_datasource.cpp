v8::Local<v8::Value> MemoryDatasource::NewInstance(mapnik::datasource_ptr ds_ptr) {
    Nan::EscapableHandleScope scope;
    MemoryDatasource* d = new MemoryDatasource();
    d->datasource_ = ds_ptr;
    v8::Local<v8::Value> ext = Nan::New<v8::External>(d);
    return scope.Escape( Nan::New(constructor)->GetFunction()->NewInstance(1, &ext));
}