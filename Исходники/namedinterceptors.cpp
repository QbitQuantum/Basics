v8::Local<v8::Value> NamedInterceptor::NewInstance () {
  EscapableHandleScope scope;
  v8::Local<v8::FunctionTemplate> constructorHandle =
      Nan::New(namedinterceptors_constructor);
  v8::Local<v8::Object> instance =
    constructorHandle->GetFunction()->NewInstance(0, NULL);
  return scope.Escape(instance);
}