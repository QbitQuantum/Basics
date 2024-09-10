static void Init (void)
{
   static const char *fragShaderText =
      "uniform float time;\n"
      "varying vec3 position;\n"
      "void main () {\n"
      "   gl_FragColor = vec4 (vec3 (0.5 + 0.5 * noise1 (vec4 (position, time))), 1.0);\n"
      "}\n"
   ;
   static const char *vertShaderText =
      "varying vec3 position;\n"
      "void main () {\n"
      "   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
      "   position = 4.0 * gl_Vertex.xyz;\n"
      "}\n"
   ;

	if (!glutExtensionSupported ("GL_ARB_fragment_shader"))
	{
		printf ("Sorry, this demo requires GL_ARB_fragment_shader\n");
		exit(1);
	}
	if (!glutExtensionSupported ("GL_ARB_shader_objects"))
	{
		printf ("Sorry, this demo requires GL_ARB_shader_objects\n");
		exit(1);
	}
	if (!glutExtensionSupported ("GL_ARB_shading_language_100"))
	{
		printf ("Sorry, this demo requires GL_ARB_shading_language_100\n");
		exit(1);
	}
	if (!glutExtensionSupported ("GL_ARB_vertex_shader"))
	{
		printf ("Sorry, this demo requires GL_ARB_vertex_shader\n");
		exit(1);
	}

	glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)
		GETPROCADDRESS("glCreateShaderObjectARB");
 	glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)
		GETPROCADDRESS("glShaderSourceARB");
 	glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)
		GETPROCADDRESS("glCompileShaderARB");
 	glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC)
		GETPROCADDRESS("glCreateProgramObjectARB");
 	glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC)
		GETPROCADDRESS("glAttachObjectARB");
 	glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC)
		GETPROCADDRESS ("glLinkProgramARB");
 	glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC)
		GETPROCADDRESS("glUseProgramObjectARB");          

	glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC)
		GETPROCADDRESS("glGetUniformLocationARB");
	glUniform1fARB = (PFNGLUNIFORM1FARBPROC)
		GETPROCADDRESS("glUniform1fARB");

	fragShader = glCreateShaderObjectARB (GL_FRAGMENT_SHADER_ARB);
	glShaderSourceARB (fragShader, 1, &fragShaderText, NULL);
	glCompileShaderARB (fragShader);

	vertShader = glCreateShaderObjectARB (GL_VERTEX_SHADER_ARB);
	glShaderSourceARB (vertShader, 1, &vertShaderText, NULL);
	glCompileShaderARB (vertShader);

	program = glCreateProgramObjectARB ();
	glAttachObjectARB (program, fragShader);
	glAttachObjectARB (program, vertShader);
	glLinkProgramARB (program);
	glUseProgramObjectARB (program);

	uTime = glGetUniformLocationARB (program, "time");

	glClearColor (0.0f, 0.1f, 0.3f, 1.0f);
	glEnable (GL_CULL_FACE);
	glEnable (GL_DEPTH_TEST);

	printf ("GL_RENDERER = %s\n", (const char *) glGetString (GL_RENDERER));
}