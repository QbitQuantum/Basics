Handle<Value> ImageHashAsync(const Arguments& args) {
    if (args.Length() < 2 || !args[1]->IsFunction()) {
        // no callback defined
        return ThrowException(Exception::Error(String::New("Callback is required and must be an Function.")));
    }

    String::Utf8Value str(args[0]);
    Handle<Function> cb = Handle<Function>::Cast(args[1]);
    
    PhashRequest* request = new PhashRequest;
    request->callback = Persistent<Function>::New(cb);
    request->file = string(*str);
    request->request.data = request;
    uv_queue_work(uv_default_loop(), &request->request, HashWorker, HashAfter);
    return Undefined();
}