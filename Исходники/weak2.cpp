v8::Local<v8::String> wrap() {
  EscapableHandleScope scope;
  v8::Local<v8::String> lstring = New("result").ToLocalChecked();
  v8::Local<v8::ObjectTemplate> otpl = New<v8::ObjectTemplate>();
  otpl->SetInternalFieldCount(1);
  v8::Local<v8::Object> obj = otpl->NewInstance();
  SetInternalFieldPointer(obj, 0, new int(42));
  Persistent<v8::Object> persistent(obj);
  persistent.SetWeak(
      static_cast<int*>(0)
    , weakCallback
    , WeakCallbackType::kInternalFields);
  assert(persistent.IsWeak());
  return scope.Escape(lstring);
}