void printable(const FunctionCallbackInfo<Value>& args)
{
	QByteArray data = ModuleByteArray::unwrapByteArray(args.GetIsolate(), args.Holder());

	QString placeholder = ".";
	if (args.Length() >= 1) {
		if (!args[0]->IsString()) {
			Utility::throwException(args.GetIsolate(), Utility::ExceptionInvalidArgumentType);
			return;
		}
		placeholder = Utility::toString(args[0]);
	}

	QString result;
	result.reserve(data.length());

	for (int i = 0; i < data.length(); i++) {
		char c = data.at(i);
		if (QChar::isPrint(c))
			result.append(c);
		else
			result.append(placeholder);
	}

	args.GetReturnValue().Set(Utility::toV8String(args.GetIsolate(), result));
}