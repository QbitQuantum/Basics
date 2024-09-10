void TargetCallback(Isolate* isolate, Persistent<Object>* target, WeakRef* arg) {
    HandleScope scope;
    if(!arg->target.IsNearDeath()) {
        return;
    }

    Local<Object> fnthis = Local<Object>::New(Isolate::GetCurrent(), arg->target);
    Handle<Value> argv[1];
    argv[0] = fnthis;

    // invoke any listening callbacks
    Local<Array> callbacks = Local<Array>::New(Isolate::GetCurrent(), arg->callbacks);
    uint32_t len = callbacks->Length();
    for (uint32_t i = 0; i < len; i++) {
        Handle<Function> cb = Handle<Function>::Cast(callbacks->Get(i));
        TryCatch try_catch;
        cb->Call(fnthis, 1, argv);
        if (try_catch.HasCaught()) {
            ThrowException(String::New("TargetCallback"));
        }
    }

    arg->target.Dispose();
    arg->target.Clear();
    arg->callbacks.Dispose();
    arg->callbacks.Clear();
}