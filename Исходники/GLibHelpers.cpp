Handle<Object> createBuffer(char *data, int length) {
	Nan::EscapableHandleScope scope;

	Local<Object> buffer = Nan::CopyBuffer(data, length).ToLocalChecked();

	return scope.Escape(buffer);
}