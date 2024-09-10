void NativeProtobuf::Init(Local<Object> exports) {
  // constructor
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);

  tpl->SetClassName(Nan::New<String>("NativeProtobuf").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // prototype
  Nan::SetPrototypeMethod(tpl, "parse", NativeProtobuf::Parse);
  Nan::SetPrototypeMethod(tpl, "parseWithUnknown",
                          NativeProtobuf::ParseWithUnknown);
  Nan::SetPrototypeMethod(tpl, "serialize", NativeProtobuf::Serialize);
  Nan::SetPrototypeMethod(tpl, "info", NativeProtobuf::Info);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New<String>("native").ToLocalChecked(), tpl->GetFunction());
}