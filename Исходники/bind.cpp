Handle<Value> ALUTInitWithoutContextCallback(const Arguments& args) {
	//if less that nbr of formal parameters then do nothing
	if (args.Length() < 2)
		return v8::Undefined();
	
	//get arguments
	Handle<Array> arg0 = Array::Cast(args[0]);
	String::Utf8Value value1(args[1]);
	char* arg1 = *value1;

	//make call
	alutInitWithoutContext((int*)arg0, (char**)arg1);
	
	return v8::Undefined();
}