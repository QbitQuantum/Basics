v8::Local<v8::String> wrap(v8::Local<v8::Function> func) {
  EscapableHandleScope scope;
  v8::Local<v8::String> lstring = New<v8::String>("result").ToLocalChecked();
  int *parameter = new int(42);
  Persistent<v8::Function> persistent(func);
  persistent.SetWeak(parameter, weakCallback, WeakCallbackType::kParameter);
  assert(persistent.IsWeak());
  return scope.Escape(lstring);
}