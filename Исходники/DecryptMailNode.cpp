void CheckPass(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Nan::Utf8String recipfile(info[0]->ToString());
	Nan::Utf8String pass(info[1]->ToString());

	//wchar_t* w_recipfile = CharToWchar_New(*recipfile);
	int ret = parse_cert_file(*recipfile, *pass,NULL);
	//delete[] w_recipfile;
	v8::Local<v8::Number> res = Nan::New(ret);
	info.GetReturnValue().Set(res);
}