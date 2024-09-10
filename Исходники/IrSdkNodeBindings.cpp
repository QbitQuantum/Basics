 void isConnected(const Nan::FunctionCallbackInfo<v8::Value>& args)
 {
   args.GetReturnValue().Set(Nan::New(irsdk.isConnected()));
 }