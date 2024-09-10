// --------------------------------------------------------
Handle<Value> NodeOpenALStream::Buffer(const Arguments& args) {
	HandleScope scope;
	NodeOpenALStream* obj = ObjectWrap::Unwrap<NodeOpenALStream>(args.This());

	if (args.Length() < 1) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close( Undefined() );
	}

	Local<Value> buffer = args[0];
	size_t size = node::Buffer::Length( buffer->ToObject() );
	char* bufferdata = node::Buffer::Data( buffer->ToObject() );

	obj->buffer(size, bufferdata);
	return scope.Close(v8::Undefined());
}