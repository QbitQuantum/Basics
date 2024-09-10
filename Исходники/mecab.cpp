void MeCab_Tagger::Init(v8::Local<v8::Object> exports) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Tagger").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "parse", Parse);
  Nan::SetPrototypeMethod(tpl, "parseToNode", ParseToNode);
  Nan::SetPrototypeMethod(tpl, "dictionaryInfo", DictionaryInfo);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("Tagger").ToLocalChecked(), tpl->GetFunction());
}