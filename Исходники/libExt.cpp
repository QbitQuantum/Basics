void    initExtensions ()
{
    static  bool    initialized = false;                    // whether initExtensions has already been called

    if ( initialized )
        return;

#ifdef  _WIN32
    glActiveTextureARB       = (PFNGLACTIVETEXTUREARBPROC)         getProcAddress ( "glActiveTextureARB"       );
    glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)   getProcAddress ( "glClientActiveTextureARB" );
    glMultiTexCoord1f        = (PFNGLMULTITEXCOORD1FARBPROC)       getProcAddress ( "glMultiTexCoord1fARB"     );
    glMultiTexCoord1fv       = (PFNGLMULTITEXCOORD1FVARBPROC)      getProcAddress ( "glMultiTexCoord1fvARB"    );
    glMultiTexCoord2f        = (PFNGLMULTITEXCOORD2FARBPROC)       getProcAddress ( "glMultiTexCoord2fARB"     );
    glMultiTexCoord2fv       = (PFNGLMULTITEXCOORD2FVARBPROC)      getProcAddress ( "glMultiTexCoord2fvARB"    );
    glMultiTexCoord3f        = (PFNGLMULTITEXCOORD3FARBPROC)       getProcAddress ( "glMultiTexCoord3fARB"     );
    glMultiTexCoord3fv       = (PFNGLMULTITEXCOORD3FVARBPROC)      getProcAddress ( "glMultiTexCoord3fvARB"    );
    glMultiTexCoord4f        = (PFNGLMULTITEXCOORD4FARBPROC)       getProcAddress ( "glMultiTexCoord4fARB"     );
    glMultiTexCoord4fv       = (PFNGLMULTITEXCOORD4FVARBPROC)      getProcAddress ( "glMultiTexCoord4fvARB"    );
#endif

    glFogCoordf              = (PFNGLFOGCOORDFEXTPROC)             getProcAddress ( "glFogCoordfEXT"         );

    glSecondaryColor3f       = (PFNGLSECONDARYCOLOR3FPROC)         getProcAddress ( "glSecondaryColor3fEXT"      );
    glSecondaryColor3fv      = (PFNGLSECONDARYCOLOR3FVPROC)        getProcAddress ( "glSecondaryColor3fvEXT"     );
    glSecondaryColorPointer  = (PFNGLSECONDARYCOLORPOINTERPROC)    getProcAddress ( "glSecondaryColorPointerEXT" );

    glCombinerParameterfvNV  = (PFNGLCOMBINERPARAMETERFVNVPROC)    getProcAddress ( "glCombinerParameterfvNV"  );
    glCombinerParameterivNV  = (PFNGLCOMBINERPARAMETERIVNVPROC)    getProcAddress ( "glCombinerParameterivNV"  );
    glCombinerParameterfNV   = (PFNGLCOMBINERPARAMETERFNVPROC)     getProcAddress ( "glCombinerParameterfNV"   );
    glCombinerParameteriNV   = (PFNGLCOMBINERPARAMETERINVPROC)     getProcAddress ( "glCombinerParameteriNV"   );
    glCombinerInputNV        = (PFNGLCOMBINERINPUTNVPROC)          getProcAddress ( "glCombinerInputNV"        );
    glCombinerOutputNV       = (PFNGLCOMBINEROUTPUTNVPROC)         getProcAddress ( "glCombinerOutputNV"       );
    glFinalCombinerInputNV   = (PFNGLFINALCOMBINERINPUTNVPROC)     getProcAddress ( "glFinalCombinerInputNV"   );

    glBindBufferARB           = (PFNGLBINDBUFFERARBPROC)           getProcAddress ( "glBindBufferARB"           );
    glDeleteBuffersARB        = (PFNGLDELETEBUFFERSARBPROC)        getProcAddress ( "glDeleteBuffersARB"        );
    glGenBuffersARB           = (PFNGLGENBUFFERSARBPROC)           getProcAddress ( "glGenBuffersARB"           );
    glIsBufferARB             = (PFNGLISBUFFERARBPROC)             getProcAddress ( "glIsBufferARB"             );
    glBufferDataARB           = (PFNGLBUFFERDATAARBPROC)           getProcAddress ( "glBufferDataARB"           );
    glBufferSubDataARB        = (PFNGLBUFFERSUBDATAARBPROC)        getProcAddress ( "glBufferSubDataARB"        );
    glGetBufferSubDataARB     = (PFNGLGETBUFFERSUBDATAARBPROC)     getProcAddress ( "glGetBufferSubDataARB"     );
    glMapBufferARB            = (PFNGLMAPBUFFERARBPROC)            getProcAddress ( "glMapBufferARB"            );
    glUnmapBufferARB          = (PFNGLUNMAPBUFFERARBPROC)          getProcAddress ( "glUnmapBufferARB"          );
    glGetBufferParameterivARB = (PFNGLGETBUFFERPARAMETERIVARBPROC) getProcAddress ( "glGetBufferParameterivARB" );
    glGetBufferPointervARB    = (PFNGLGETBUFFERPOINTERVARBPROC)    getProcAddress ( "glGetBufferPointervARB"    );

                                    // NV-occlusion query extension
    glGenOcclusionQueriesNV = (PFNGLGENOCCLUSIONQUERIESNVPROC) getProcAddress ( "glGenOcclusionQueriesNV" );
    glBeginOcclusionQueryNV = (PFNGLBEGINOCCLUSIONQUERYNVPROC) getProcAddress ( "glBeginOcclusionQueryNV" );
    glEndOcclusionQueryNV   = (PFNGLENDOCCLUSIONQUERYNVPROC)   getProcAddress ( "glEndOcclusionQueryNV"   );
    glGetOcclusionQueryivNV = (PFNGLGETOCCLUSIONQUERYIVNVPROC) getProcAddress ( "glGetOcclusionQueryivNV" );

                                    // ARB_vertex_program extension
    glGenProgramsARB                = (PFNGLGENPROGRAMSARBPROC)               getProcAddress ( "glGenProgramsARB" );
    glDeleteProgramsARB             = (PFNGLDELETEPROGRAMSARBPROC)            getProcAddress ( "glDeleteProgramsARB" );
    glBindProgramARB                = (PFNGLBINDPROGRAMARBPROC)               getProcAddress ( "glBindProgramARB" );
    glIsProgramARB                  = (PFNGLISPROGRAMARBPROC)                 getProcAddress ( "glIsProgramARB" );
    glProgramStringARB              = (PFNGLPROGRAMSTRINGARBPROC)             getProcAddress ( "glProgramStringARB" );
    glGetProgramivARB               = (PFNGLGETPROGRAMIVARBPROC)              getProcAddress ( "glGetProgramivARB" );
    glVertexAttrib4fARB             = (PFNGLVERTEXATTRIB4FARBPROC)            getProcAddress ( "glVertexAttrib4fARB" );
    glVertexAttrib4fvARB            = (PFNGLVERTEXATTRIB4FVARBPROC)           getProcAddress ( "glVertexAttrib4fvARB" );
    glVertexAttrib3fARB             = (PFNGLVERTEXATTRIB3FARBPROC)            getProcAddress ( "glVertexAttrib3fARB" );
    glVertexAttrib3fvARB            = (PFNGLVERTEXATTRIB3FVARBPROC)           getProcAddress ( "glVertexAttrib3fvARB" );
    glVertexAttribPointerARB        = (PFNGLVERTEXATTRIBPOINTERARBPROC)       getProcAddress ( "glVertexAttribPointerARB" );
    glEnableVertexAttribArrayARB    = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)   getProcAddress ( "glEnableVertexAttribArrayARB" );
    glDisableVertexAttribArrayARB   = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)  getProcAddress ( "glDisableVertexAttribArrayARB" );
    glProgramLocalParameter4fARB    = (PFNGLPROGRAMLOCALPARAMETER4FARBPROC)   getProcAddress ( "glProgramLocalParameter4fARB" );
    glProgramLocalParameter4fvARB   = (PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)  getProcAddress ( "glProgramLocalParameter4fvARB" );
    glGetProgramLocalParameterfvARB = (PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC)getProcAddress ( "glGetProgramLocalParameterfvARB" );
    glProgramEnvParameter4fARB      = (PFNGLPROGRAMENVPARAMETER4FARBPROC)     getProcAddress ( "glProgramEnvParameter4fARB" );
    glProgramEnvParameter4fvARB     = (PFNGLPROGRAMENVPARAMETER4FVARBPROC)    getProcAddress ( "glProgramEnvParameter4fvARB" );
    glGetProgramEnvParameterfvARB   = (PFNGLGETPROGRAMENVPARAMETERFVARBPROC)  getProcAddress ( "glGetProgramEnvParameterfvARB" );

                                    // GL_EXT_texture3D
    glTexImage3DEXT                 =(PFNGLTEXIMAGE3DEXTPROC)                 getProcAddress ( "glTexImage3DEXT" );

                                    // ARB_texture_compression
    glCompressedTexImage3DARB       = (PFNGLCOMPRESSEDTEXIMAGE3DARBPROC)      getProcAddress ( "glCompressedTexImage3DARB"    );
    glCompressedTexImage2DARB       = (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC)      getProcAddress ( "glCompressedTexImage2DARB"    );
    glCompressedTexImage1DARB       = (PFNGLCOMPRESSEDTEXIMAGE1DARBPROC)      getProcAddress ( "glCompressedTexImage1DARB"    );
    glCompressedTexSubImage3DARB    = (PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC)   getProcAddress ( "glCompressedTexSubImage3DARB" );
    glCompressedTexSubImage2DARB    = (PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC)   getProcAddress ( "glCompressedTexSubImage2DARB" );
    glCompressedTexSubImage1DARB    = (PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC)   getProcAddress ( "glCompressedTexSubImage1DARB" );
    glGetCompressedTexImageARB      = (PFNGLGETCOMPRESSEDTEXIMAGEARBPROC)     getProcAddress ( "glGetCompressedTexImageARB"   );

                                    // ARB_point_parameters
    glPointParameterfARB             = (PFNGLPOINTPARAMETERFARBPROC)          getProcAddress ( "glPointParameterfARB" );
    glPointParameterfvARB            = (PFNGLPOINTPARAMETERFVARBPROC)         getProcAddress ( "glPointParameterfvARB" );

                                    // ARB_occlusion_query
    glGenQueriesARB        = (PFNGLGENQUERIESARBPROC)        getProcAddress ( "glGenQueriesARB"        );
    glDeleteQueriesARB     = (PFNGLDELETEQUERIESARBPROC)     getProcAddress ( "glDeleteQueriesARB"     );
    glIsQueryARB           = (PFNGLISQUERYARBPROC)           getProcAddress ( "glIsQueryARB"           );
    glBeginQueryARB        = (PFNGLBEGINQUERYARBPROC)        getProcAddress ( "glBeginQueryARB"        );
    glEndQueryARB          = (PFNGLENDQUERYARBPROC)          getProcAddress ( "glEndQueryARB"          );
    glGetQueryivARB        = (PFNGLGETQUERYIVARBPROC)        getProcAddress ( "glGetQueryivARB"        );
    glGetQueryObjectivARB  = (PFNGLGETQUERYOBJECTIVARBPROC)  getProcAddress ( "glGetQueryObjectivARB"  );
    glGetQueryObjectuivARB = (PFNGLGETQUERYOBJECTUIVARBPROC) getProcAddress ( "glGetQueryObjectuivARB" );

                                    // GLSL-specific extensions
                                    // GL_ARB_shader_object
    glDeleteObjectARB         = (PFNGLDELETEOBJECTARBPROC)         getProcAddress ( "glDeleteObjectARB" );
    glGetHandleARB            = (PFNGLGETHANDLEARBPROC)            getProcAddress ( "glGetHandleARB" );
    glDetachObjectARB         = (PFNGLDETACHOBJECTARBPROC)         getProcAddress ( "glDetachObjectARB" );
    glCreateShaderObjectARB   = (PFNGLCREATESHADEROBJECTARBPROC)   getProcAddress ( "glCreateShaderObjectARB" );
    glShaderSourceARB         = (PFNGLSHADERSOURCEARBPROC)         getProcAddress ( "glShaderSourceARB" );
    glCompileShaderARB        = (PFNGLCOMPILESHADERARBPROC)        getProcAddress ( "glCompileShaderARB" );
    glCreateProgramObjectARB  = (PFNGLCREATEPROGRAMOBJECTARBPROC)  getProcAddress ( "glCreateProgramObjectARB" );
    glAttachObjectARB         = (PFNGLATTACHOBJECTARBPROC)         getProcAddress ( "glAttachObjectARB" );
    glLinkProgramARB          = (PFNGLLINKPROGRAMARBPROC)          getProcAddress ( "glLinkProgramARB" );
    glUseProgramObjectARB     = (PFNGLUSEPROGRAMOBJECTARBPROC)     getProcAddress ( "glUseProgramObjectARB" );
    glValidateProgramARB      = (PFNGLVALIDATEPROGRAMARBPROC)      getProcAddress ( "glValidateProgramARB" );
    glUniform1fARB            = (PFNGLUNIFORM1FARBPROC)            getProcAddress ( "glUniform1fARB" );
    glUniform2fARB            = (PFNGLUNIFORM2FARBPROC)            getProcAddress ( "glUniform2fARB" );
    glUniform3fARB            = (PFNGLUNIFORM3FARBPROC)            getProcAddress ( "glUniform3fARB" );
    glUniform4fARB            = (PFNGLUNIFORM4FARBPROC)            getProcAddress ( "glUniform4fARB" );
    glUniform1iARB            = (PFNGLUNIFORM1IARBPROC)            getProcAddress ( "glUniform1iARB" );
    glUniform2iARB            = (PFNGLUNIFORM2IARBPROC)            getProcAddress ( "glUniform2iARB" );
    glUniform3iARB            = (PFNGLUNIFORM3IARBPROC)            getProcAddress ( "glUniform3iARB" );
    glUniform4iARB            = (PFNGLUNIFORM4IARBPROC)            getProcAddress ( "glUniform4iARB" );
    glUniform1fvARB           = (PFNGLUNIFORM1FVARBPROC)           getProcAddress ( "glUniform1fvARB" );
    glUniform2fvARB           = (PFNGLUNIFORM2FVARBPROC)           getProcAddress ( "glUniform2fvARB" );
    glUniform3fvARB           = (PFNGLUNIFORM3FVARBPROC)           getProcAddress ( "glUniform3fvARB" );
    glUniform4fvARB           = (PFNGLUNIFORM4FVARBPROC)           getProcAddress ( "glUniform4fvARB" );
    glUniform1ivARB           = (PFNGLUNIFORM1IVARBPROC)           getProcAddress ( "glUniform1ivARB" );
    glUniform2ivARB           = (PFNGLUNIFORM2IVARBPROC)           getProcAddress ( "glUniform2ivARB" );
    glUniform3ivARB           = (PFNGLUNIFORM3IVARBPROC)           getProcAddress ( "glUniform3ivARB" );
    glUniform4ivARB           = (PFNGLUNIFORM4IVARBPROC)           getProcAddress ( "glUniform4ivARB" );
    glUniformMatrix2fvARB     = (PFNGLUNIFORMMATRIX2FVARBPROC)     getProcAddress ( "glUniformMatrix2fvARB" );
    glUniformMatrix3fvARB     = (PFNGLUNIFORMMATRIX3FVARBPROC)     getProcAddress ( "glUniformMatrix3fvARB" );
    glUniformMatrix4fvARB     = (PFNGLUNIFORMMATRIX4FVARBPROC)     getProcAddress ( "glUniformMatrix4fvARB" );
    glGetObjectParameterfvARB = (PFNGLGETOBJECTPARAMETERFVARBPROC) getProcAddress ( "glGetObjectParameterfvARB" );
    glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC) getProcAddress ( "glGetObjectParameterivARB" );
    glGetInfoLogARB           = (PFNGLGETINFOLOGARBPROC)           getProcAddress ( "glGetInfoLogARB" );
    glGetAttachedObjectsARB   = (PFNGLGETATTACHEDOBJECTSARBPROC)   getProcAddress ( "glGetAttachedObjectsARB" );
    glGetUniformLocationARB   = (PFNGLGETUNIFORMLOCATIONARBPROC)   getProcAddress ( "glGetUniformLocationARB" );
    glGetActiveUniformARB     = (PFNGLGETACTIVEUNIFORMARBPROC)     getProcAddress ( "glGetActiveUniformARB" );
    glGetUniformfvARB         = (PFNGLGETUNIFORMFVARBPROC)         getProcAddress ( "glGetUniformfvARB" );
    glGetUniformivARB         = (PFNGLGETUNIFORMIVARBPROC)         getProcAddress ( "glGetUniformivARB" );
    glGetShaderSourceARB      = (PFNGLGETSHADERSOURCEARBPROC)      getProcAddress ( "glGetShaderSourceARB" );

                                        // GL_ARB_vertex_shader
    glBindAttribLocationARB   = (PFNGLBINDATTRIBLOCATIONARBPROC)   getProcAddress ( "glBindAttribLocationARB" );
    glGetActiveAttribARB      = (PFNGLGETACTIVEATTRIBARBPROC)      getProcAddress ( "glGetActiveAttribARB"    );
    glGetAttribLocationARB    = (PFNGLGETATTRIBLOCATIONARBPROC)    getProcAddress ( "glGetAttribLocationARB"  );
    glGetVertexAttribfvARB    = (PFNGLGETVERTEXATTRIBFVARBPROC)    getProcAddress ( "glGetVertexAttribfvARB"  );

                                        // EXT_stencil_two_side
    glActiveStencilFaceEXT    = (PFNGLACTIVESTENCILFACEEXTPROC)    getProcAddress ( "glActiveStencilFaceEXT" );

										// EXT_depth_bounds_test
	glDepthBoundsEXT      = (PFNGLDEPTHBOUNDSEXTPROC)          getProcAddress ( "glDepthBoundsEXT" );

										// EXT_framebuffer_object
	glIsRenderbufferEXT                      = (PFNGLISRENDERBUFFEREXTPROC                     ) getProcAddress ( "glIsRenderbufferEXT" );
	glBindRenderbufferEXT                    = (PFNGLBINDRENDERBUFFEREXTPROC                   ) getProcAddress ( "glBindRenderbufferEXT" );
	glDeleteRenderbuffersEXT                 = (PFNGLDELETERENDERBUFFERSEXTPROC                ) getProcAddress ( "glDeleteRenderbuffersEXT" );
	glGenRenderbuffersEXT                    = (PFNGLGENRENDERBUFFERSEXTPROC                   ) getProcAddress ( "glGenRenderbuffersEXT" );
	glRenderbufferStorageEXT                 = (PFNGLRENDERBUFFERSTORAGEEXTPROC                ) getProcAddress ( "glRenderbufferStorageEXT" );
	glGetRenderbufferParameterivEXT          = (PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC         ) getProcAddress ( "glGetRenderbufferParameterivEXT" );
	glIsFramebufferEXT                       = (PFNGLISFRAMEBUFFEREXTPROC                      ) getProcAddress ( "glIsFramebufferEXT" );
	glBindFramebufferEXT                     = (PFNGLBINDFRAMEBUFFEREXTPROC                    ) getProcAddress ( "glBindFramebufferEXT" );
	glDeleteFramebuffersEXT                  = (PFNGLDELETEFRAMEBUFFERSEXTPROC                 ) getProcAddress ( "glDeleteFramebuffersEXT" );
	glGenFramebuffersEXT                     = (PFNGLGENFRAMEBUFFERSEXTPROC                    ) getProcAddress ( "glGenFramebuffersEXT" );
	glCheckFramebufferStatusEXT              = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC             ) getProcAddress ( "glCheckFramebufferStatusEXT" );
	glFramebufferTexture1DEXT                = (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC               ) getProcAddress ( "glFramebufferTexture1DEXT" );
	glFramebufferTexture2DEXT                = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC               ) getProcAddress ( "glFramebufferTexture2DEXT" );
	glFramebufferTexture3DEXT                = (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC               ) getProcAddress ( "glFramebufferTexture3DEXT" );
	glFramebufferRenderbufferEXT             = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC			   ) getProcAddress ( "glFramebufferRenderbufferEXT" );
	glGetFramebufferAttachmentParameterivEXT = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) getProcAddress ( "glGetFramebufferAttachmentParameterivEXT" );
	glGenerateMipmapEXT                      = (PFNGLGENERATEMIPMAPEXTPROC					   ) getProcAddress ( "glGenerateMipmapEXT" );

#ifndef	GL_VERSION_1_3										// ARB_transpose matrix
	glLoadTransposeMatrixfARB	              = (PFNGLLOADTRANSPOSEMATRIXFPROC                 ) getProcAddress ( "glLoadTransposeMatrixfARB" );
	glLoadTransposeMatrixdARB	              = (PFNGLLOADTRANSPOSEMATRIXDPROC                 ) getProcAddress ( "glLoadTransposeMatrixdARB" );
	glMultTransposeMatrixfARB	              = (PFNGLMULTTRANSPOSEMATRIXFPROC                 ) getProcAddress ( "glMultTransposeMatrixfARB" );
	glMultTransposeMatrixdARB	              = (PFNGLMULTTRANSPOSEMATRIXDPROC                 ) getProcAddress ( "glMultTransposeMatrixdARB" );
#endif	

															// ARB_color_buffer_float
	glClampColorARB         = (PFNGLCLAMPCOLORARBPROC)      getProcAddress ( "glClampColorARB" );

#ifdef	_WIN32											// fresh Linux already has 2.0
														// stencil ops from OpenGL 2.0
	glStencilFuncSeparate  = (PFNGLSTENCILFUNCSEPARATEPROC) getProcAddress ( "glStencilFuncSeparate" );
	glStencilOpSeparate    = (PFNGLSTENCILOPSEPARATEPROC)   getProcAddress ( "glStencilOpSeparate" );
	glStencilMaskSeparate  = (PFNGLSTENCILMASKSEPARATEPROC) getProcAddress ( "glStencilMaskSeparate" );

															// blend ops from OPenGL 2.0
	glBlendEquation         = (PFNGLBLENDEQUATIONPROC)         getProcAddress ( "glBlendEquation" );
	glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC) getProcAddress ( "glBlendEquationSeparate" );
	glBlendFuncSeparate     = (PFNGLBLENDFUNCSEPARATEPROC)     getProcAddress ( "glBlendFuncSeparate" );
	glBlendColor            = (PFNGLBLENDCOLORPROC)            getProcAddress ( "glBlendColor" );
#endif

															// draw buffers from OpenGL 2.0
	glDrawBuffers           = (PFNGLDRAWBUFFERSPROC)           getProcAddress ( "glDrawBuffers" );
															// ATI_draw_buffers
	glDrawBuffersATI        = (PFNGLDRAWBUFFERSATIPROC)        getProcAddress ( "glDrawBuffersATI" );
	
#ifdef  _WIN32
    initWin32Extensions ();
#else
    initLinuxExtensions ();
#endif

    initialized = true;
}