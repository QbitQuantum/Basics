void GetClipDatabase(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if ((info.Length() < 1) || (info.Length() > 1)) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  int sizeOfData = 0;
  char* clipDatabase = GetClipDatabase(sizeOfData);

  v8::Local<v8::String> v8ClipDatabase = v8::String::New(clipDatabase, sizeOfData);
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  obj->Set(Nan::New("msg").ToLocalChecked(), v8ClipDatabase);
  info.GetReturnValue().Set(obj);

  FreeClipDatabase(clipDatabase);
}