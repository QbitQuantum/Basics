v8::Handle<v8::Value> V8CharacterData::appendDataCallback(const v8::Arguments& args) {

	v8::Local<v8::Object> self = args.Holder();
	struct V8CharacterDataPrivate* privData = V8DOM::toClassPtr<V8CharacterDataPrivate >(self->GetInternalField(0));
	if (false) {
	} else if (args.Length() == 1 &&
	           args[0]->IsString()) {
		v8::String::AsciiValue localArg(args[0]);

		privData->nativeObj->appendData(*localArg);

		return v8::Undefined();
	}
	throw V8Exception("Parameter mismatch while calling appendData");
	return v8::Undefined();
}