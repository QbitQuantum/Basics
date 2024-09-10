void jsCreateMyClass(const FunctionCallbackInfo<Value>& args)
{
	if (args.Length() != 1)
	{
		args.GetIsolate()->ThrowException(
			String::NewFromUtf8(args.GetIsolate(), "Bad parameters",
			NewStringType::kNormal).ToLocalChecked());
		return;
	}

	Isolate* isolate = args.GetIsolate();

	Local<ObjectTemplate> myClassTemplate =
		Local<ObjectTemplate>::New(isolate, gMyClassTemplate);

	Local<Object> myClassObj = myClassTemplate->NewInstance(
		isolate->GetCurrentContext()).ToLocalChecked();

	int numValue =
		args[0]->Int32Value(isolate->GetCurrentContext()).FromMaybe(0);

	gMyClass = new ObjectWrap(numValue);
	gMyClass->Wrap(myClassObj);

	args.GetReturnValue().Set(myClassObj);
}