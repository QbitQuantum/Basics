Handle<Value> NovaConfigBinding::SetDoppelInterface(const Arguments& args)
{
	HandleScope scope;
	
	if(args.Length() != 1)
	{
		return ThrowException(Exception::TypeError(String::New("Must be invoked with one parameter")));
	}
	
	NovaConfigBinding* obj = ObjectWrap::Unwrap<NovaConfigBinding>(args.This());
	std::string difToSet = cvv8::CastFromJS<std::string>(args[0]);
	
	obj->m_conf->SetDoppelInterface(difToSet);
	
	return args.This();
}