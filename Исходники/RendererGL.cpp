void RendererGL::initGLExtensions()
{
	// nullify the pointers
	glBindBufferARB           = NULL;
	glDeleteBuffersARB        = NULL;
	glGenBuffersARB           = NULL;
	glIsBufferARB             = NULL;
	glBufferDataARB           = NULL;
	glBufferSubDataARB        = NULL;
	glGetBufferSubDataARB     = NULL;
	glMapBufferARB            = NULL;
	glUnmapBufferARB          = NULL;
	glGetBufferParameterivARB = NULL;
	glGetBufferPointervARB    = NULL;
	glActiveTextureARB			= NULL;
	glClientActiveTextureARB	= NULL;

	// set the bool query storage to all false
	memset(&m_supported[0], 0, sizeof(bool)*MAX_EXTENSIONS);

	const unsigned char* ext = glGetString (GL_EXTENSIONS);
	std::string ext_str = (char*)ext;
/*
	std::ofstream extensionDump("extensions.txt");
	extensionDump << ext_str;
	extensionDump.close();
*/

	// GL_ARB_multitexture
	if(std::string::npos != ext_str.find("GL_ARB_multitexture") )
	{
		m_supported[XGL_ARB_multitexture] = true;

		/* Obtain the address of the extension entry points. */
		glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)	getProcAddress("glActiveTextureARB");
		glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC) getProcAddress("glClientActiveTextureARB");
		// Load the rest IF you need them, no need to store unused function pointers, yes I am lazy as well..
/*
		glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)	getProcAddress("glMultiTexCoord2fARB");
		glMultiTexCoord1dARB = (PFNGLMULTITEXCOORD1DARBPROC) getProcAddress("glMultiTexCoord1dARB");
        glMultiTexCoord1dvARB = (PFNGLMULTITEXCOORD1DVARBPROC) getProcAddress("glMultiTexCoord1dvARB");
        glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FARBPROC) getProcAddress("glMultiTexCoord1fARB");
        glMultiTexCoord1fvARB = (PFNGLMULTITEXCOORD1FVARBPROC) getProcAddress("glMultiTexCoord1fvARB");
        glMultiTexCoord1iARB = (PFNGLMULTITEXCOORD1IARBPROC) getProcAddress("glMultiTexCoord1iARB");
        glMultiTexCoord1ivARB = (PFNGLMULTITEXCOORD1IVARBPROC) getProcAddress("glMultiTexCoord1ivARB");
        glMultiTexCoord1sARB = (PFNGLMULTITEXCOORD1SARBPROC) getProcAddress("glMultiTexCoord1sARB");
        glMultiTexCoord1svARB = (PFNGLMULTITEXCOORD1SVARBPROC) getProcAddress("glMultiTexCoord1svARB");
        glMultiTexCoord2dARB = (PFNGLMULTITEXCOORD2DARBPROC) getProcAddress("glMultiTexCoord2dARB");
        glMultiTexCoord2dvARB = (PFNGLMULTITEXCOORD2DVARBPROC) getProcAddress("glMultiTexCoord2dvARB");
        glMultiTexCoord2fvARB = (PFNGLMULTITEXCOORD2FVARBPROC) getProcAddress("glMultiTexCoord2fvARB");
        glMultiTexCoord2iARB = (PFNGLMULTITEXCOORD2IARBPROC) getProcAddress("glMultiTexCoord2iARB");
        glMultiTexCoord2ivARB = (PFNGLMULTITEXCOORD2IVARBPROC) getProcAddress("glMultiTexCoord2ivARB");
        glMultiTexCoord2sARB = (PFNGLMULTITEXCOORD2SARBPROC) getProcAddress("glMultiTexCoord2sARB");
        glMultiTexCoord2svARB = (PFNGLMULTITEXCOORD2SVARBPROC) getProcAddress("glMultiTexCoord2svARB");
        glMultiTexCoord3dARB = (PFNGLMULTITEXCOORD3DARBPROC) getProcAddress("glMultiTexCoord3dARB");
        glMultiTexCoord3dvARB = (PFNGLMULTITEXCOORD3DVARBPROC) getProcAddress("glMultiTexCoord3dvARB");
        glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FARBPROC) getProcAddress("glMultiTexCoord3fARB");
        glMultiTexCoord3fvARB = (PFNGLMULTITEXCOORD3FVARBPROC) getProcAddress("glMultiTexCoord3fvARB");
        glMultiTexCoord3iARB = (PFNGLMULTITEXCOORD3IARBPROC) getProcAddress("glMultiTexCoord3iARB");
        glMultiTexCoord3ivARB = (PFNGLMULTITEXCOORD3IVARBPROC) getProcAddress("glMultiTexCoord3ivARB");
        glMultiTexCoord3sARB = (PFNGLMULTITEXCOORD3SARBPROC) getProcAddress("glMultiTexCoord3sARB");
        glMultiTexCoord3svARB = (PFNGLMULTITEXCOORD3SVARBPROC) getProcAddress("glMultiTexCoord3svARB");
        glMultiTexCoord4dARB = (PFNGLMULTITEXCOORD4DARBPROC) getProcAddress("glMultiTexCoord4dARB");
        glMultiTexCoord4dvARB = (PFNGLMULTITEXCOORD4DVARBPROC) getProcAddress("glMultiTexCoord4dvARB");
        glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FARBPROC) getProcAddress("glMultiTexCoord4fARB");
        glMultiTexCoord4fvARB = (PFNGLMULTITEXCOORD4FVARBPROC) getProcAddress("glMultiTexCoord4fvARB");
        glMultiTexCoord4iARB = (PFNGLMULTITEXCOORD4IARBPROC) getProcAddress("glMultiTexCoord4iARB");
        glMultiTexCoord4ivARB = (PFNGLMULTITEXCOORD4IVARBPROC) getProcAddress("glMultiTexCoord4ivARB");
        glMultiTexCoord4sARB = (PFNGLMULTITEXCOORD4SARBPROC) getProcAddress("glMultiTexCoord4sARB");
        glMultiTexCoord4svARB = (PFNGLMULTITEXCOORD4SVARBPROC) getProcAddress("glMultiTexCoord4svARB");
*/
    }
	
	// GL_ARB_vertex_buffer_object
	if(std::string::npos != ext_str.find("GL_ARB_vertex_buffer_object") )
	{
		m_supported[XGL_ARB_vertex_buffer_object] = true;
		glBindBufferARB           = (PFNGLBINDBUFFERARBPROC)getProcAddress("glBindBufferARB");
        glDeleteBuffersARB        = (PFNGLDELETEBUFFERSARBPROC)getProcAddress("glDeleteBuffersARB");
        glGenBuffersARB           = (PFNGLGENBUFFERSARBPROC)getProcAddress("glGenBuffersARB");
        glIsBufferARB             = (PFNGLISBUFFERARBPROC)getProcAddress("glIsBufferARB");
        glBufferDataARB           = (PFNGLBUFFERDATAARBPROC)getProcAddress("glBufferDataARB");
        glBufferSubDataARB        = (PFNGLBUFFERSUBDATAARBPROC)getProcAddress("glBufferSubDataARB");
        glGetBufferSubDataARB     = (PFNGLGETBUFFERSUBDATAARBPROC)getProcAddress("glGetBufferSubDataARB");
        glMapBufferARB            = (PFNGLMAPBUFFERARBPROC)getProcAddress("glMapBufferARB");
        glUnmapBufferARB          = (PFNGLUNMAPBUFFERARBPROC)getProcAddress("glUnmapBufferARB");
        glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC)getProcAddress("glGetBufferParameterivARB");
        glGetBufferPointervARB    = (PFNGLGETBUFFERPOINTERVARBPROC)getProcAddress("glGetBufferPointervARB");
	}
}