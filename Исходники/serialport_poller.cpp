void SerialportPoller::Init(Handle<Object> target) {
  Nan::HandleScope scope;

  // Prepare constructor template
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New<String>("SerialportPoller").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);


  // Prototype

  // SerialportPoller.close()
  Nan::SetPrototypeTemplate(tpl, "close",
      Nan::GetFunction(Nan::New<FunctionTemplate>(Close)).ToLocalChecked());

  // SerialportPoller.start()
  Nan::SetPrototypeTemplate(tpl, "start",
      Nan::GetFunction(Nan::New<FunctionTemplate>(Start)).ToLocalChecked());

  serialportpoller_constructor.Reset(tpl);

  Nan::Set(target, Nan::New<String>("SerialportPoller").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}