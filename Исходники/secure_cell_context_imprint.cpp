 void SecureCellContextImprint::decrypt(const Nan::FunctionCallbackInfo<v8::Value>& args) {
   SecureCellContextImprint* obj = Nan::ObjectWrap::Unwrap<SecureCellContextImprint>(args.This());
   size_t length=0;
   const uint8_t* context=(const uint8_t*)(node::Buffer::Data(args[1]));
   size_t context_length=node::Buffer::Length(args[1]);
   if(themis_secure_cell_decrypt_context_imprint(&(obj->key_)[0], obj->key_.size(), (const uint8_t*)(node::Buffer::Data(args[0])), node::Buffer::Length(args[0]), context, context_length, NULL, &length)!=THEMIS_BUFFER_TOO_SMALL){
     Nan::ThrowError("Secure Cell (Context Imprint) failed  decrypting");
     args.GetReturnValue().SetUndefined();
     return;
   }
   uint8_t* data=(uint8_t*)(malloc(length));
   if(themis_secure_cell_decrypt_context_imprint(&(obj->key_)[0], obj->key_.size(), (const uint8_t*)(node::Buffer::Data(args[0])), node::Buffer::Length(args[0]), context, context_length, data, &length)!=THEMIS_SUCCESS){
     Nan::ThrowError("Secure Cell (Context Imprint) failed  decrypting");
     free(data);
     args.GetReturnValue().SetUndefined();
     return;
   }
   args.GetReturnValue().Set(Nan::NewBuffer((char*)(data), length).ToLocalChecked());
 }