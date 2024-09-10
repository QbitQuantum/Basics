v8::Local<v8::Value> MSOutputFormat::NewInstance(outputFormatObj *of_ptr) {
  Nan::EscapableHandleScope scope;
  MSOutputFormat* of = new MSOutputFormat();
  of->this_ = of_ptr;
  v8::Local<v8::Value> ext = Nan::New<v8::External>(of);
  return scope.Escape(Nan::New(constructor)->GetFunction()->NewInstance(1, &ext));
}