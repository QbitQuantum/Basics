void BookWrap::Each(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    HandleScope scope(isolate);

    Book* book = ObjectWrap::Unwrap<BookWrap>(args.This())->m_book;

    if (args.Length() == 1) {
        if (args[0]->IsFunction()) {
            Local<Function> fun = Local<Function>::Cast(args[0]);
            for(uint32_t i = 0; i < book->size(); ++i) {
                Local<Object> pw = PersonWrap::New(isolate, book, i);
                Local<Value> argv[1] = { pw };
                fun->Call(Null(isolate), 1, argv);
            }
            args.GetReturnValue().SetUndefined();
            return;
        }
        else {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Function expected")));
            args.GetReturnValue().SetUndefined();
            return;
        }
    }
    else {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "One argument expected")));
        args.GetReturnValue().SetUndefined();
        return;
            
    }
}