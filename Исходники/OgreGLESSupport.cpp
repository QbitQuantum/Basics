    void GLESSupport::initialiseExtensions(void)
    {
        // Set version string
        const GLubyte* pcVer = glGetString(GL_VERSION);

        assert(pcVer && "Problems getting GL version string using glGetString");

        String tmpStr = (const char*)pcVer;
        LogManager::getSingleton().logMessage("GL_VERSION = " + tmpStr);
        mVersion = tmpStr.substr(0, tmpStr.find(" "));

        // Get vendor
        const GLubyte* pcVendor = glGetString(GL_VENDOR);
        tmpStr = (const char*)pcVendor;
        LogManager::getSingleton().logMessage("GL_VENDOR = " + tmpStr);
        mVendor = tmpStr.substr(0, tmpStr.find(" "));

        // Get renderer
        const GLubyte* pcRenderer = glGetString(GL_RENDERER);
        tmpStr = (const char*)pcRenderer;
        LogManager::getSingleton().logMessage("GL_RENDERER = " + tmpStr);

        // Set extension list
        std::stringstream ext;
        String str;

        const GLubyte* pcExt = glGetString(GL_EXTENSIONS);
        LogManager::getSingleton().logMessage("GL_EXTENSIONS = " + String((const char*)pcExt));

        assert(pcExt && "Problems getting GL extension string using glGetString");

        ext << pcExt;

        while (ext >> str)
        {
			LogManager::getSingleton().logMessage("EXT:" + str);
            extensionList.insert(str);
        }


		// Get function pointers on platforms that doesn't have prototypes
#ifndef GL_GLEXT_PROTOTYPES

		// define the GL types if they are not defined
#	ifndef PFNGLISRENDERBUFFEROES

		// GL_OES_Framebuffer_object

		typedef GLboolean (GL_APIENTRY *PFNGLISRENDERBUFFEROES)(GLuint renderbuffer);
		typedef void (GL_APIENTRY *PFNGLBINDRENDERBUFFEROES)(GLenum target, GLuint renderbuffer);
		typedef void (GL_APIENTRY *PFNGLDELETERENDERBUFFERSOES)(GLsizei n, const GLuint *renderbuffers);
		typedef void (GL_APIENTRY *PFNGLGENRENDERBUFFERSOES)(GLsizei n, GLuint *renderbuffers);
		typedef void (GL_APIENTRY *PFNGLRENDERBUFFERSTORAGEOES)(GLenum target, GLenum internalformat,GLsizei width, GLsizei height);
		typedef void (GL_APIENTRY *PFNGLGETRENDERBUFFERPARAMETERIVOES)(GLenum target, GLenum pname, GLint* params);
		typedef GLboolean (GL_APIENTRY *PFNGLISFRAMEBUFFEROES)(GLuint framebuffer);
		typedef void (GL_APIENTRY *PFNGLBINDFRAMEBUFFEROES)(GLenum target, GLuint framebuffer);
		typedef void (GL_APIENTRY *PFNGLDELETEFRAMEBUFFERSOES)(GLsizei n, const GLuint *framebuffers);
		typedef void (GL_APIENTRY *PFNGLGENFRAMEBUFFERSOES)(GLsizei n, GLuint *framebuffers);
		typedef GLenum (GL_APIENTRY *PFNGLCHECKFRAMEBUFFERSTATUSOES)(GLenum target);
		typedef void (GL_APIENTRY *PFNGLFRAMEBUFFERTEXTURE2DOES)(GLenum target, GLenum attachment,GLenum textarget, GLuint texture,GLint level);
		typedef void (GL_APIENTRY *PFNGLFRAMEBUFFERRENDERBUFFEROES)(GLenum target, GLenum attachment,GLenum renderbuffertarget, GLuint renderbuffer);
		typedef void (GL_APIENTRY *PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOES)(GLenum target, GLenum attachment,GLenum pname, GLint *params);
		typedef void (GL_APIENTRY *PFNGLGENERATEMIPMAPOES)(GLenum target);

		typedef void (GL_APIENTRY *PFNGLBLENDEQUATIONOES)(GLenum mode);
		typedef void (GL_APIENTRY *PFNGLBLENDFUNCSEPARATEOES)(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
		typedef void (GL_APIENTRY *PFNGLBLENDEQUATIONSEPARATEOES)(GLenum modeRGB, GLenum modeAlpha);

        typedef void* (GL_APIENTRY *PFNGLMAPBUFFEROES)(GLenum target, GLenum access);
        typedef GLboolean (GL_APIENTRY *PFNGLUNMAPBUFFEROES)(GLenum target);

		// GL_OES_point_size_array
		typedef void (GL_APIENTRY *PFNGLPOINTSIZEPOINTEROES)(GLenum type, GLsizei stride, const void *ptr );
#	endif

        glIsRenderbufferOES = (PFNGLISRENDERBUFFEROES)getProcAddress("glIsRenderbufferOES");
        glBindRenderbufferOES = (PFNGLBINDRENDERBUFFEROES)getProcAddress("glBindRenderbufferOES");
        glDeleteRenderbuffersOES = (PFNGLDELETERENDERBUFFERSOES)getProcAddress("glDeleteRenderbuffersOES");
        glGenRenderbuffersOES = (PFNGLGENRENDERBUFFERSOES)getProcAddress("glGenRenderbuffersOES");
        glRenderbufferStorageOES = (PFNGLRENDERBUFFERSTORAGEOES)getProcAddress("glRenderbufferStorageOES");
        glGetRenderbufferParameterivOES = (PFNGLGETRENDERBUFFERPARAMETERIVOES)getProcAddress("glGetRenderbufferParameterivOES");
        glIsFramebufferOES = (PFNGLISFRAMEBUFFEROES)getProcAddress("glIsFramebufferOES");
        glBindFramebufferOES = (PFNGLBINDFRAMEBUFFEROES)getProcAddress("glBindFramebufferOES");
        glDeleteFramebuffersOES = (PFNGLDELETEFRAMEBUFFERSOES)getProcAddress("glDeleteFramebuffersOES");
        glGenFramebuffersOES = (PFNGLGENFRAMEBUFFERSOES)getProcAddress("glGenFramebuffersOES");
        glCheckFramebufferStatusOES = (PFNGLCHECKFRAMEBUFFERSTATUSOES)getProcAddress("glCheckFramebufferStatusOES");
        glFramebufferRenderbufferOES = (PFNGLFRAMEBUFFERRENDERBUFFEROES)getProcAddress("glFramebufferRenderbufferOES");
        glFramebufferTexture2DOES = (PFNGLFRAMEBUFFERTEXTURE2DOES)getProcAddress("glFramebufferTexture2DOES");
        glGetFramebufferAttachmentParameterivOES = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOES)getProcAddress("glGetFramebufferAttachmentParameterivOES");
        glGenerateMipmapOES = (PFNGLGENERATEMIPMAPOES)getProcAddress("glGenerateMipmapOES");

		glBlendEquationOES = (PFNGLBLENDEQUATIONOES)getProcAddress("glBlendEquationOES");
		glBlendFuncSeparateOES = (PFNGLBLENDFUNCSEPARATEOES)getProcAddress("glBlendFuncSeparateOES");
		glBlendEquationSeparateOES = (PFNGLBLENDEQUATIONSEPARATEOES)getProcAddress("glBlendEquationSeparateOES");

        glMapBufferOES = (PFNGLMAPBUFFEROES)getProcAddress("glMapBufferOES");
        glUnmapBufferOES = (PFNGLUNMAPBUFFEROES)getProcAddress("glUnmapBufferOES");
#endif
    }