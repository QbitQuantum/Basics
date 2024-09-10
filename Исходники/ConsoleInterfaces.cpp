void ConsoleInterfaces::Assert(const FunctionCallbackInfo<Value>& args)
{
	Handle<External> ext = Handle<External>::Cast(args.Data());
	Flathead *pFH = (Flathead *)ext->Value();
	int counter = 0;

	if (args.Length() == 0)
	{
		pFH->GetConfiguration()->LoggingFn()(LogLevels::Assert, "");
		return;
	}

	Local<Value> value = args[0];

	if (value->IsTrue())
	{
		args.GetReturnValue().Set(counter);
		return;
	}

	if (pFH->GetConfiguration()->LoggingFn() != NULL)
	{
		for (int i = 1; i < args.Length(); i++)
		{
			Local<Value> value = args[i];

			String::Utf8Value outputString(value);

			pFH->GetConfiguration()->LoggingFn()(LogLevels::Assert, *outputString);
			counter++;
		}
	}

	args.GetReturnValue().Set(counter);
}