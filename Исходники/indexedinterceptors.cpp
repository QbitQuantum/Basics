v8::Local<v8::Value> IndexedInterceptor::NewInstance () {
  EscapableHandleScope scope;
  v8::Local<v8::FunctionTemplate> constructorHandle =
      Nan::New(indexedinterceptors_constructor);
  v8::Local<v8::Object> instance =
    Nan::NewInstance(constructorHandle->GetFunction()).ToLocalChecked();
  return scope.Escape(instance);
}