void Tempest::Detail::ImplDeviceBase::initExt() {
  const char * ext = (const char*)glGetString(GL_EXTENSIONS);
  if( ext==nullptr )
    ext = "";
  const char *renderer= (const char*)glGetString(GL_RENDERER);

  T_ASSERT_X(ext!=nullptr, "opengl context not created");

  hasS3tcTextures =
      (strstr(ext, "GL_OES_texture_compression_S3TC")!=nullptr) ||
      (strstr(ext, "GL_EXT_texture_compression_s3tc")!=nullptr);
  hasETC1Textures       = (strstr(ext, "GL_OES_compressed_ETC1_RGB8_texture")!=nullptr);
  hasWriteonlyRendering = (strstr(ext, "GL_QCOM_writeonly_rendering")!=nullptr);

  hasNpotTexture = (strstr(ext, "GL_OES_texture_npot")!=nullptr) ||
                   (strstr(ext, "GL_ARB_texture_non_power_of_two")!=nullptr);

  hasHalfSupport            = (strstr(ext, "GL_OES_vertex_half_float")!=nullptr) ||
                              (strstr(ext, "GL_ARB_half_float_vertex")!=nullptr);

#ifdef __ANDROID__
  hasRenderToRGBTexture     =  strstr(ext, "GL_OES_rgb8_rgba8")!=0;
  hasRenderToRGBATexture    = (strstr(ext, "GL_OES_rgb8_rgba8")!=0)||(strstr(ext, "GL_ARM_rgba8")!=0);
#else
  hasRenderToRGBTexture     = 1;
  hasRenderToRGBATexture    = 1;
#endif
  hasTextureFloat           = strstr(ext, "GL_ARB_texture_float")!=nullptr;
  hasPackedFloat            = strstr(ext, "GL_EXT_packed_float") !=nullptr;

  hasQCOMTiles      = strstr(ext, "GL_QCOM_tiled_rendering")   !=nullptr;
  hasDiscardBuffers = strstr(ext, "GL_EXT_discard_framebuffer")!=nullptr;

#ifdef __WINDOWS__
  if( strstr(ext, "WGL_EXT_swap_control") ){
    wglSwapInterval = (Detail::PFNGLWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");
    }
#endif

  hasTileBasedRender = hasQCOMTiles | hasDiscardBuffers;

#ifdef __ANDROID__
  if( hasQCOMTiles ){
    glStartTilingQCOM = (Detail::PFNGLSTARTTILINGQCOMPROC)eglGetProcAddress("glStartTilingQCOM");
    glEndTilingQCOM   =   (Detail::PFNGLENDTILINGQCOMPROC)eglGetProcAddress("glEndTilingQCOM");
    }

  if( hasDiscardBuffers ){
    glDiscardFrameBuffer = (Detail::PFNGLDISCARDFRAMEBUFFERPROC)eglGetProcAddress("glDiscardFramebufferEXT");
    }
#endif
#ifdef __IOS__
  if( hasQCOMTiles ){
    glStartTilingQCOM = 0;
    glEndTilingQCOM   = 0;
    }

  if( hasDiscardBuffers ){
    this->glDiscardFrameBuffer = 0;
    hasDiscardBuffers=false;//TODO
    }
#endif

  caps.hasHalf2 = hasHalfSupport;
  caps.hasHalf4 = hasHalfSupport;
  caps.hasRedableDepth = ((strstr(ext, "GL_OES_depth_texture")!=nullptr) ||
                          (strstr(ext, "GL_ARB_depth_texture")!=nullptr)) &&
                         (strcmp(renderer,"PowerVR SGX 540")!=0);//PVR bug
  caps.hasNativeRGB =hasRenderToRGBTexture;
  caps.hasNativeRGBA=hasRenderToRGBATexture;

  glGetIntegerv( GL_MAX_TEXTURE_SIZE,         &caps.maxTextureSize );
#ifdef __MOBILE_PLATFORM__
  glGetIntegerv( GL_MAX_VARYING_VECTORS,      &caps.maxVaryingVectors );
  caps.maxVaryingComponents = caps.maxVaryingVectors*4;
#else
  glGetIntegerv( GL_MAX_VARYING_COMPONENTS,   &caps.maxVaryingComponents );
  caps.maxVaryingVectors = caps.maxVaryingComponents/4;
#endif

#ifdef GL_MAX_FRAGMENT_UNIFORM_COMPONENTS
  glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS,  &caps.maxVertexUniformVectors  );
  glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,&caps.maxFragmentUniformVectors);
  caps.maxVertexUniformVectors   /= 4;
  caps.maxFragmentUniformVectors /= 4;
#else
  glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS,&caps.maxFragmentUniformVectors);
  glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS,  &caps.maxVertexUniformVectors  );
#endif
  //T_ASSERT_X( errCk(), "OpenGL error" );

#ifdef __MOBILE_PLATFORM__
  caps.maxRTCount = 1;
#else
  glGetIntegerv( GL_MAX_COLOR_ATTACHMENTS, &caps.maxRTCount );
  if( caps.maxRTCount>32 )
    caps.maxRTCount = 32;
#endif
  caps.hasNpotTexture = hasNpotTexture;
  wglSwapInterval = 0;
  }