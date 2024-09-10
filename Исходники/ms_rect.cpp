v8::Local<v8::Value> MSRect::NewInstance(rectObj *ptr) {
  Nan::EscapableHandleScope scope;
  MSRect* obj = new MSRect();
  obj->this_ = ptr;
  v8::Local<v8::Value> ext = Nan::New<v8::External>(obj);
  return scope.Escape(Nan::New(constructor)->GetFunction()->NewInstance(1, &ext));
}