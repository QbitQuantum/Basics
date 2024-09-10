JSValue JSFunction::operator()(const JSArgs& args) {
  return operator()(JSGlobalObject(), args);
}