    static NAN_MODULE_INIT(Init)
    {
        Nan::HandleScope scope;

        v8::Local<v8::FunctionTemplate> t = Nan::New<v8::FunctionTemplate>(Device::New);

        s_ct.Reset(t);
        t->SetClassName(Nan::New<v8::String>("Device").ToLocalChecked());
        t->InstanceTemplate()->SetInternalFieldCount(1);

        Nan::SetPrototypeMethod(t, "getRootNode", GetRootNode);

        target->Set(Nan::New<v8::String>("Device").ToLocalChecked(), t->GetFunction());
    }