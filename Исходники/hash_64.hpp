    static void Initialize(Handle<Object> target) {
      Local<String> name = Nan::New<String>("XXHash64").ToLocalChecked();
      Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);

      tpl->InstanceTemplate()->SetInternalFieldCount(1);
      tpl->SetClassName(name);

      Nan::SetPrototypeMethod(tpl, "update", Update);
      Nan::SetPrototypeMethod(tpl, "digest", Digest);

      Nan::SetMethod(tpl, "hash", StaticHash);
      target->Set(name, tpl->GetFunction());

      constructor_64.Reset(tpl);
    }