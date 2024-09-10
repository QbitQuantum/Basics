void PersistentDisposeContext::CallDisposeOnV8Thread() {
    DBG("PersistentDisposeContext::CallDisposeOnV8Thread");

    Nan::Persistent<v8::Value>* handle = (Nan::Persistent<v8::Value>*)ptr.ToPointer();
    handle->Reset();
    delete handle;
}