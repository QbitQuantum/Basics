Handle<Value> GLESglGetShaderSourceCallback(const Arguments& args) {
	if (args.Length() != 1)
		return v8::Undefined();
	
	//get arguments
	unsigned shader = args[0]->Uint32Value();

	//query string length
	int len = 0;
	glGetShaderiv((GLuint)shader, GL_SHADER_SOURCE_LENGTH, &len);

	char* log = new char[len];
	glGetShaderSource((GLuint)shader, (GLsizei)len, NULL, log);

	return String::New(log);
}