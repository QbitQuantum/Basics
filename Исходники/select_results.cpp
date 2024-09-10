Local<Object> SelectResults::NewInstance(const SelectResultsPtr & selectResultsPtr) {
  Nan::EscapableHandleScope scope;
 const unsigned int argc = 0;
  Local<Value> argv[argc] = {};
  Local<Object> instance(Nan::New(SelectResults::constructor())->NewInstance(argc, argv));
  SelectResults * selectResults = new SelectResults(selectResultsPtr);
  selectResults->Wrap(instance);

  return scope.Escape(instance);
}