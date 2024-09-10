v8::Local<v8::Value> SetterGetter::NewInstance () {
  EscapableHandleScope scope;
  v8::Local<v8::FunctionTemplate> constructorHandle =
      Nan::New(settergetter_constructor);
  v8::Local<v8::Object> instance =
    constructorHandle->GetFunction()->NewInstance(0, NULL);
  SetAccessor(
      instance
    , Nan::New("prop1").ToLocalChecked()
    , SetterGetter::GetProp1);
  SetAccessor(
      instance
    , Nan::New<v8::String>("prop2").ToLocalChecked()
    , SetterGetter::GetProp2
    , SetterGetter::SetProp2
  );
  return scope.Escape(instance);
}