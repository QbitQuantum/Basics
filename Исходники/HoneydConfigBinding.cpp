Handle<Value> HoneydConfigBinding::RenamePortset(const Arguments& args)
{
	HandleScope scope;
	HoneydConfigBinding* obj = ObjectWrap::Unwrap<HoneydConfigBinding>(args.This());

	if(args.Length() != 3)
	{
		return ThrowException(Exception::TypeError(String::New("Must be invoked with 3 parameters")));
	}

	std::string oldName = cvv8::CastFromJS<string>(args[0]);
	std::string newName = cvv8::CastFromJS<string>(args[1]);
	std::string profile = cvv8::CastFromJS<string>(args[2]);

	return scope.Close(Boolean::New(obj->m_conf->RenamePortset(profile, oldName, newName)));
}