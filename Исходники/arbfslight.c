static void Init (void)
{
   static const char *fragShaderText =
      "uniform vec3 lightPos;\n"
      "uniform vec4 diffuse;\n"
      "uniform vec4 specular;\n"
      "varying vec3 normal;\n"
      "void main () {\n"
      "   // Compute dot product of light direction and normal vector\n"
      "   float dotProd = max (dot (lightPos, normalize (normal)), 0.0);\n"
      "   // Compute diffuse and specular contributions\n"
#if 1
      "   gl_FragColor = diffuse * dotProd + specular * pow (dotProd, 20.0);\n"
#elif 1 /* test IF/ELSE/ENDIF */
      "   if (normal.y > 0.0) { \n"
      "      gl_FragColor = diffuse * dotProd + specular * pow (dotProd, 20.0);\n"
      "   } \n"
      "   else { \n"
      "      if (normal.x < 0.0) { \n"
      "         gl_FragColor = vec4(1, 0, 0, 0); \n"
      "      } \n"
      "      else { \n"
      "         gl_FragColor = vec4(1, 1, 0, 0); \n"
      "      } \n"
      "   } \n"
#elif 1 /* test LOOP */
      "   while (1) { \n"
      "      if (normal.y >= 0.0) { \n"
      "         gl_FragColor = vec4(1, 0, 0, 0); \n"
      "         break; \n"
      "      } else { \n"
      "         gl_FragColor = diffuse * dotProd + specular * pow (dotProd, 20.0);\n"
      "         break; \n"
      "      } \n"
      "   } \n"
#endif
      "}\n"
   ;
   static const char *vertShaderText =
      "varying vec3 normal;\n"
      "void main () {\n"
      "   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
      "   normal = gl_NormalMatrix * gl_Normal;\n"
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

	glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC) GETPROCADDRESS ("glCreateShaderObjectARB");
	glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC) GETPROCADDRESS ("glShaderSourceARB");
	glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC) GETPROCADDRESS ("glCompileShaderARB");
	glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC) GETPROCADDRESS ("glCreateProgramObjectARB");
	glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC) GETPROCADDRESS ("glAttachObjectARB");
	glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC) GETPROCADDRESS ("glLinkProgramARB");
	glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC) GETPROCADDRESS ("glUseProgramObjectARB");
	glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC) GETPROCADDRESS ("glGetUniformLocationARB");
   glUniform3fvARB = (PFNGLUNIFORM3FVARBPROC) GETPROCADDRESS ("glUniform3fvARB");
   glUniform4fvARB = (PFNGLUNIFORM3FVARBPROC) GETPROCADDRESS ("glUniform4fvARB");

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

	uLightPos = glGetUniformLocationARB (program, "lightPos");
	uDiffuse = glGetUniformLocationARB (program, "diffuse");
	uSpecular = glGetUniformLocationARB (program, "specular");

   glUniform4fvARB (uDiffuse, 1, diffuse);
   glUniform4fvARB (uSpecular, 1, specular);

	glClearColor (0.3f, 0.3f, 0.3f, 0.0f);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_LIGHT0);
	glEnable (GL_LIGHTING);
	glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 20.0f);

	printf ("GL_RENDERER = %s\n", (const char *) glGetString (GL_RENDERER));
	printf ("Press p to toggle between per-pixel and per-vertex lighting\n");
}