v8::Local<v8::Value> MSLayers::NewInstance(mapObj *ptr) {
  Nan::EscapableHandleScope scope;
  MSLayers* obj = new MSLayers();
  obj->this_ = ptr;
  v8::Local<v8::Value> ext = Nan::New<v8::External>(obj);
  return scope.Escape(Nan::New(constructor)->GetFunction()->NewInstance(1, &ext));
}