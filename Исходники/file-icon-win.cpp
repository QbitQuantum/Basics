void Init(Handle<Object> exports, Handle<Object> module) {
  Set(module, New<String>("exports").ToLocalChecked(),
      GetFunction(New<FunctionTemplate>(Get)).ToLocalChecked());
}