void CallSetImmediate::call() {
	csIsolate->protectedScope([this](){
		v8::Isolate* isolate = v8::Isolate::GetCurrent(); v8::HandleScope scope(isolate);
		auto cb = v8::Local<v8::Function>::New(isolate, pcb);
		pcb.Dispose();
		delete this;
		cb->Call(v8::Context::GetCurrent()->Global(), 0, nullptr);
		_InterlockedDecrement(&outStandingCallbacks);
	});
}