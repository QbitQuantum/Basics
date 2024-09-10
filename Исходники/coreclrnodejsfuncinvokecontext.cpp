void CoreClrNodejsFuncInvokeContext::InvokeCallback(void* data)
{
	DBG("CoreClrNodejsFuncInvokeContext::InvokeCallback");

	CoreClrNodejsFuncInvokeContext* context = (CoreClrNodejsFuncInvokeContext*) data;
	v8::Local<v8::Value> v8Payload = CoreClrFunc::MarshalCLRToV8(context->Payload, context->PayloadType);

	static Nan::Persistent<v8::Function> callbackFactory;
	static Nan::Persistent<v8::Function> callbackFunction;

	Nan::HandleScope scope;

	// See https://github.com/tjanczuk/edge/issues/125 for context
	if (callbackFactory.IsEmpty())
	{
		v8::Local<v8::Function> v8FuncCallbackFunction = Nan::New<v8::FunctionTemplate>(coreClrV8FuncCallback)->GetFunction();
		callbackFunction.Reset(v8FuncCallbackFunction);
		v8::Local<v8::String> code = Nan::New<v8::String>(
			"(function (cb, ctx) { return function (e, d) { return cb(e, d, ctx); }; })").ToLocalChecked();
		v8::Local<v8::Function> callbackFactoryFunction = v8::Local<v8::Function>::Cast(v8::Script::Compile(code)->Run());
		callbackFactory.Reset(callbackFactoryFunction);
	}

	v8::Local<v8::Value> factoryArgv[] = { Nan::New(callbackFunction), Nan::New<v8::External>((void*)context) };
	v8::Local<v8::Function> callback = v8::Local<v8::Function>::Cast(
		Nan::New(callbackFactory)->Call(Nan::GetCurrentContext()->Global(), 2, factoryArgv));

	v8::Local<v8::Value> argv[] = { v8Payload, callback };
	TryCatch tryCatch;

	DBG("CoreClrNodejsFuncInvokeContext::InvokeCallback - Calling JavaScript function");
	Nan::Call(Nan::New(*(context->FunctionContext->Func)), Nan::GetCurrentContext()->Global(), 2, argv);
	DBG("CoreClrNodejsFuncInvokeContext::InvokeCallback - Called JavaScript function");

	if (tryCatch.HasCaught())
	{
		DBG("CoreClrNodejsFuncInvokeContext::InvokeCallback - Caught JavaScript exception");

		void* exceptionData;
		CoreClrFunc::MarshalV8ExceptionToCLR(tryCatch.Exception(), &exceptionData);

		DBG("CoreClrNodejsFuncInvokeContext::InvokeCallback - Exception message is: %s", (char*)exceptionData);

		context->Complete(TaskStatusFaulted, exceptionData, V8TypeException);
	}
    else
    {
        // Kick the next tick
        CallbackHelper::KickNextTick();
    }
}