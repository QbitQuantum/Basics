///////////////////////////////////////////////////////////////////////
//load, compile and set the shaders
void setShaders()
{
	char *vs,*fs,*gs;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	g = glCreateShader(GL_GEOMETRY_SHADER);

	vs = textFileRead("./shader01.vert");
	fs = textFileRead("./shader01.frag");
	gs = textFileRead("./shader01.geom");

	const char * ff = fs;
	const char * vv = vs;
	const char * gg = gs;

	GL_CHECK(glShaderSource(v, 1, &vv,NULL));
	GL_CHECK(glShaderSource(f, 1, &ff,NULL));
	GL_CHECK(glShaderSource(g, 1, &gg,NULL));

	free(vs);free(fs);free(gs);

	GL_CHECK(glCompileShader(v));
	GL_CHECK(glCompileShader(f));
	GL_CHECK(glCompileShader(g));

	GLint blen = 0;
	GLsizei slen = 0;

	glGetShaderiv(v, GL_INFO_LOG_LENGTH , &blen);
	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);
		glGetShaderInfoLog(v, blen, &slen, compiler_log);
		std::cout << "compiler_log vertex shader:\n" << compiler_log << std::endl;
		free (compiler_log);
	}
	blen = 0;
	slen = 0;
	glGetShaderiv(f, GL_INFO_LOG_LENGTH , &blen);
	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);
		glGetShaderInfoLog(f, blen, &slen, compiler_log);
		std::cout << "compiler_log fragment shader:\n" << compiler_log << std::endl;
		free (compiler_log);
	}
	blen = 0;
	slen = 0;
	glGetShaderiv(g, GL_INFO_LOG_LENGTH , &blen);
	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);
		glGetShaderInfoLog(g, blen, &slen, compiler_log);
		std::cout << "compiler_log geometry shader:\n" << compiler_log << std::endl;
		free (compiler_log);
	}

	p = glCreateProgram();

	GL_CHECK(glAttachShader(p,f));
	GL_CHECK(glAttachShader(p,v));
	GL_CHECK(glAttachShader(p,g));

	GL_CHECK(glLinkProgram(p));
	//comment out this line to not use the shader
	GL_CHECK(glUseProgram(p));
}