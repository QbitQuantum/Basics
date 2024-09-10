  void Init()
  {
    Internal("Config::Init","()");

#ifndef REGAL_NO_GETENV
    const char *tmp;

#if !REGAL_FORCE_ES1_PROFILE
    tmp = GetEnv( "REGAL_FORCE_ES1_PROFILE" );
    if (tmp) forceES1Profile = atoi(tmp)!=0;
#endif

#if !REGAL_FORCE_ES2_PROFILE
    tmp = GetEnv( "REGAL_FORCE_ES2_PROFILE" );
    if (tmp) forceES2Profile = atoi(tmp)!=0;
#endif

#if !REGAL_FORCE_CORE_PROFILE
    tmp = GetEnv( "REGAL_FORCE_CORE_PROFILE" );
    if (tmp) forceCoreProfile = atoi(tmp)!=0;
#endif

  // With REGAL_SYS_GLX && REGAL_SYS_EGL
  // we infer each from other, if specified,
  // to behave as a toggle.

#if REGAL_SYS_GLX
    tmp = GetEnv( "REGAL_SYS_GLX" );
    if (tmp)
    {
      sysGLX = atoi(tmp)!=0;
#if REGAL_SYS_EGL
      sysEGL = !sysGLX;
#endif
    }
#endif

#if REGAL_SYS_EGL
    tmp = GetEnv( "REGAL_SYS_EGL" );
    if (tmp)
    {
      sysEGL = atoi(tmp)!=0;
#if REGAL_SYS_GLX
      sysGLX = !sysEGL;
#endif
     }
#endif

    // Default to GLX, if necessary

#if REGAL_SYS_GLX && REGAL_SYS_EGL
    if (sysGLX && sysEGL)
      sysEGL = false;
#endif

#if !REGAL_FORCE_EMULATION
    tmp = GetEnv( "REGAL_FORCE_EMULATION" );
    if (tmp) forceEmulation = atoi(tmp)!=0;
#endif

#if REGAL_EMULATION
    tmp = GetEnv( "REGAL_EMULATION" );
    if (tmp) enableEmulation = atoi(tmp)!=0;
#endif

    // Deprecated

    tmp = GetEnv( "REGAL_NO_EMULATION" );
    if (tmp) enableEmulation = atoi(tmp)==0;

#if REGAL_DEBUG
    tmp = GetEnv( "REGAL_DEBUG" );
    if (tmp) enableDebug = atoi(tmp)!=0;
#endif

#if REGAL_TRACE
    tmp = GetEnv( "REGAL_TRACE" );
    if (tmp) enableTrace = atoi(tmp)!=0;
#endif

#if REGAL_ERROR
    tmp = GetEnv( "REGAL_ERROR" );
    if (tmp) enableError = atoi(tmp)!=0;
#endif

#if REGAL_CODE
    tmp = GetEnv( "REGAL_CODE" );
    if (tmp) enableCode = atoi(tmp)!=0;
#endif

#if REGAL_LOG
    tmp = GetEnv( "REGAL_LOG" );
    if (tmp) enableLog = atoi(tmp)!=0;
#endif

#if REGAL_DRIVER
    tmp = GetEnv( "REGAL_DRIVER" );
    if (tmp) enableDriver = atoi(tmp)!=0;
#endif

#if REGAL_EMU_PPA
    tmp = GetEnv( "REGAL_EMU_PPA" );
    if (tmp) enableEmuPpa = atoi(tmp)!=0;
#endif

#if REGAL_EMU_PPCA
    tmp = GetEnv( "REGAL_EMU_PPCA" );
    if (tmp) enableEmuPpca = atoi(tmp)!=0;
#endif

#if REGAL_EMU_OBJ
    tmp = GetEnv( "REGAL_EMU_OBJ" );
    if (tmp) enableEmuObj = atoi(tmp)!=0;
#endif

#if REGAL_EMU_BIN
    tmp = GetEnv( "REGAL_EMU_BIN" );
    if (tmp) enableEmuBin = atoi(tmp)!=0;
#endif

#if REGAL_EMU_TEXSTO
    tmp = GetEnv( "REGAL_EMU_TEXSTO" );
    if (tmp) enableEmuTexSto = atoi(tmp)!=0;
#endif

#if REGAL_EMU_XFER
    tmp = GetEnv( "REGAL_EMU_XFER" );
    if (tmp) enableEmuXfer = atoi(tmp)!=0;
#endif

#if REGAL_EMU_DSA
    tmp = GetEnv( "REGAL_EMU_DSA" );
    if (tmp) enableEmuDsa = atoi(tmp)!=0;
#endif

#if REGAL_EMU_RECT
    tmp = GetEnv( "REGAL_EMU_RECT" );
    if (tmp) enableEmuRect = atoi(tmp)!=0;
#endif

#if REGAL_EMU_IFF
    tmp = GetEnv( "REGAL_EMU_IFF" );
    if (tmp) enableEmuIff = atoi(tmp)!=0;
#endif

#if REGAL_EMU_SO
    tmp = GetEnv( "REGAL_EMU_SO" );
    if (tmp) enableEmuSo = atoi(tmp)!=0;
#endif

#if REGAL_EMU_VAO
    tmp = GetEnv( "REGAL_EMU_VAO" );
    if (tmp) enableEmuVao = atoi(tmp)!=0;
#endif

#if REGAL_EMU_TEXC
    tmp = GetEnv( "REGAL_EMU_TEXC" );
    if (tmp) enableEmuTexC = atoi(tmp)!=0;
#endif

#if REGAL_EMU_FILTER
    tmp = GetEnv( "REGAL_EMU_FILTER" );
    if (tmp) enableEmuFilter = atoi(tmp)!=0;
#endif

    //

#if REGAL_EMU_PPA
    tmp = GetEnv( "REGAL_FORCE_EMU_PPA" );
    if (tmp) forceEmuPpa = atoi(tmp)!=0;
#endif

#if REGAL_EMU_PPCA
    tmp = GetEnv( "REGAL_FORCE_EMU_PPCA" );
    if (tmp) forceEmuPpca = atoi(tmp)!=0;
#endif

#if REGAL_EMU_OBJ
    tmp = GetEnv( "REGAL_FORCE_EMU_OBJ" );
    if (tmp) forceEmuObj = atoi(tmp)!=0;
#endif

#if REGAL_EMU_BIN
    tmp = GetEnv( "REGAL_FORCE_EMU_BIN" );
    if (tmp) forceEmuBin = atoi(tmp)!=0;
#endif

#if REGAL_EMU_TEXSTO
    tmp = GetEnv( "REGAL_FORCE_EMU_TEXSTO" );
    if (tmp) forceEmuTexSto = atoi(tmp)!=0;
#endif

#if REGAL_EMU_XFER
    tmp = GetEnv( "REGAL_FORCE_EMU_XFER" );
    if (tmp) forceEmuXfer = atoi(tmp)!=0;
#endif

#if REGAL_EMU_DSA
    tmp = GetEnv( "REGAL_FORCE_EMU_DSA" );
    if (tmp) forceEmuDsa = atoi(tmp)!=0;
#endif

#if REGAL_EMU_RECT
    tmp = GetEnv( "REGAL_FORCE_EMU_RECT" );
    if (tmp) forceEmuRect = atoi(tmp)!=0;
#endif

#if REGAL_EMU_IFF
    tmp = GetEnv( "REGAL_FORCE_EMU_IFF" );
    if (tmp) forceEmuIff = atoi(tmp)!=0;
#endif

#if REGAL_EMU_SO
    tmp = GetEnv( "REGAL_FORCE_EMU_SO" );
    if (tmp) forceEmuSo = atoi(tmp)!=0;
#endif

#if REGAL_EMU_VAO
    tmp = GetEnv( "REGAL_FORCE_EMU_VAO" );
    if (tmp) forceEmuVao = atoi(tmp)!=0;
#endif

#if REGAL_EMU_TEXC
    tmp = GetEnv( "REGAL_FORCE_EMU_TEXC" );
    if (tmp) forceEmuTexC = atoi(tmp)!=0;
#endif

#if REGAL_EMU_FILTER
    tmp = GetEnv( "REGAL_FORCE_EMU_FILTER" );
    if (tmp) forceEmuFilter = atoi(tmp)!=0;
#endif

    //

    tmp = GetEnv( "REGAL_FRAME_LIMIT" );
    if (tmp) frameLimit = atoi(tmp);

    //

    tmp = GetEnv( "REGAL_MD5_COLOR" );
    if (tmp) frameMd5Color = atoi(tmp)!=0;

    tmp = GetEnv( "REGAL_MD5_STENCIL" );
    if (tmp) frameMd5Stencil = atoi(tmp)!=0;

    tmp = GetEnv( "REGAL_MD5_DEPTH" );
    if (tmp) frameMd5Depth = atoi(tmp)!=0;

    tmp = GetEnv( "REGAL_MD5_COLOR_MASK" );
    if (tmp) frameMd5ColorMask = static_cast<unsigned char>(atoi(tmp));

    tmp = GetEnv( "REGAL_MD5_STENCIL_MASK" );
    if (tmp) frameMd5StencilMask = static_cast<unsigned char>(atoi(tmp));

    tmp = GetEnv( "REGAL_MD5_DEPTH_MASK" );
    if (tmp) frameMd5DepthMask = atoi(tmp);

    //

    tmp = GetEnv( "REGAL_SAVE_COLOR" );
    if (tmp) frameSaveColor = atoi(tmp)!=0;

    tmp = GetEnv( "REGAL_SAVE_STENCIL" );
    if (tmp) frameSaveStencil = atoi(tmp)!=0;

    tmp = GetEnv( "REGAL_SAVE_DEPTH" );
    if (tmp) frameSaveDepth = atoi(tmp)!=0;

    // Caching

#if REGAL_CACHE
    tmp = GetEnv( "REGAL_CACHE" );
    if (tmp) cache = atoi(tmp)!=0;

    // GLSL shader caching

#if REGAL_CACHE_SHADER
    tmp = GetEnv( "REGAL_CACHE_SHADER" );
    if (tmp) cacheShader = atoi(tmp)!=0;
#endif

#if REGAL_CACHE_SHADER_WRITE
    tmp = GetEnv( "REGAL_CACHE_SHADER_WRITE" );
    if (tmp) cacheShaderWrite = atoi(tmp)!=0;
#endif

#if REGAL_CACHE_SHADER_READ
    tmp = GetEnv( "REGAL_CACHE_SHADER_READ" );
    if (tmp) cacheShaderRead = atoi(tmp)!=0;
#endif

    // Teture caching

#if REGAL_CACHE_TEXTURE
    tmp = GetEnv( "REGAL_CACHE_TEXTURE" );
    if (tmp) cacheTexture = atoi(tmp)!=0;
#endif

#if REGAL_CACHE_TEXTURE_WRITE
    tmp = GetEnv( "REGAL_CACHE_TEXTURE_WRITE" );
    if (tmp) cacheTextureWrite = atoi(tmp)!=0;
#endif

#if REGAL_CACHE_TEXTURE_READ
    tmp = GetEnv( "REGAL_CACHE_TEXTURE_READ" );
    if (tmp) cacheTextureRead = atoi(tmp)!=0;
#endif

    tmp = GetEnv( "REGAL_CACHE_DIRECTORY" );
    if (tmp) cacheDirectory = tmp;
#endif

#if REGAL_CODE
    tmp = GetEnv( "REGAL_CODE_SOURCE" );
    if (tmp) codeSourceFile = tmp;

    tmp = GetEnv( "REGAL_CODE_HEADER" );
    if (tmp) codeHeaderFile = tmp;
#endif

#endif

#if REGAL_THREAD_LOCKING
    tmp = GetEnv( "REGAL_THREAD_LOCKING" );
    if (tmp) enableThreadLocking = atoi(tmp)!=0;
#else
    enableThreadLocking = false;
#endif

    // REGAL_NO_EMULATION is deprecated, use REGAL_EMULATION=0 instead.

#if REGAL_EMULATION && defined(REGAL_NO_EMULATION) && REGAL_NO_EMULATION
    enableEmulation = false;
#endif

#if REGAL_SYS_ES1
    Info("REGAL_FORCE_ES1_PROFILE   ", forceES1Profile  ? "enabled" : "disabled");
#endif

#if REGAL_SYS_ES2
    Info("REGAL_FORCE_ES2_PROFILE   ", forceES2Profile  ? "enabled" : "disabled");
#endif

    Info("REGAL_FORCE_CORE_PROFILE  ", forceCoreProfile ? "enabled" : "disabled");

#if REGAL_SYS_ES1
    Info("REGAL_SYS_ES1             ", sysES1           ? "enabled" : "disabled");
#endif

#if REGAL_SYS_ES2
    Info("REGAL_SYS_ES2             ", sysES2           ? "enabled" : "disabled");
#endif

#if REGAL_SYS_GL
    Info("REGAL_SYS_GL              ", sysGL            ? "enabled" : "disabled");
#endif

#if REGAL_SYS_GLX
    Info("REGAL_SYS_GLX             ", sysGLX           ? "enabled" : "disabled");
#endif

#if REGAL_SYS_EGL
    Info("REGAL_SYS_EGL             ", sysEGL           ? "enabled" : "disabled");
#endif

    Info("REGAL_FORCE_EMULATION     ", forceEmulation   ? "enabled" : "disabled");
#if REGAL_TRACE
    Info("REGAL_TRACE               ", enableTrace      ? "enabled" : "disabled");
#endif
    Info("REGAL_DEBUG               ", enableDebug      ? "enabled" : "disabled");
    Info("REGAL_ERROR               ", enableError      ? "enabled" : "disabled");
#if REGAL_CODE
    Info("REGAL_CODE                ", enableCode       ? "enabled" : "disabled");
#endif
    Info("REGAL_EMULATION           ", enableEmulation  ? "enabled" : "disabled");
    Info("REGAL_LOG                 ", enableLog        ? "enabled" : "disabled");
    Info("REGAL_DRIVER              ", enableDriver     ? "enabled" : "disabled");

    Info("REGAL_EMU_PPA             ", enableEmuPpa     ? "enabled" : "disabled");
    Info("REGAL_EMU_PPCA            ", enableEmuPpca    ? "enabled" : "disabled");
    Info("REGAL_EMU_OBJ             ", enableEmuObj     ? "enabled" : "disabled");
    Info("REGAL_EMU_BIN             ", enableEmuBin     ? "enabled" : "disabled");
    Info("REGAL_EMU_TEXSTO          ", enableEmuTexSto  ? "enabled" : "disabled");
    Info("REGAL_EMU_XFER            ", enableEmuXfer    ? "enabled" : "disabled");
    Info("REGAL_EMU_DSA             ", enableEmuDsa     ? "enabled" : "disabled");
    Info("REGAL_EMU_RECT            ", enableEmuRect    ? "enabled" : "disabled");
    Info("REGAL_EMU_IFF             ", enableEmuIff     ? "enabled" : "disabled");
    Info("REGAL_EMU_SO              ", enableEmuSo      ? "enabled" : "disabled");
    Info("REGAL_EMU_VAO             ", enableEmuVao     ? "enabled" : "disabled");
    Info("REGAL_EMU_FILTER          ", enableEmuFilter  ? "enabled" : "disabled");
    Info("REGAL_EMU_TEXC            ", enableEmuTexC    ? "enabled" : "disabled");

    Info("REGAL_FORCE_EMU_PPA       ", forceEmuPpa      ? "enabled" : "disabled");
    Info("REGAL_FORCE_EMU_PPCA      ", forceEmuPpca     ? "enabled" : "disabled");
    Info("REGAL_FORCE_EMU_OBJ       ", forceEmuObj      ? "enabled" : "disabled");
    Info("REGAL_FORCE_EMU_BIN       ", forceEmuBin      ? "enabled" : "disabled");
    Info("REGAL_FORCE_EMU_TEXSTO    ", forceEmuTexSto   ? "enabled" : "disabled");
    Info("REGAL_FORCE_EMU_XFER      ", forceEmuXfer     ? "enabled" : "disabled");
    Info("REGAL_FORCE_EMU_DSA       ", forceEmuDsa      ? "enabled" : "disabled");
    Info("REGAL_FORCE_EMU_RECT      ", forceEmuRect     ? "enabled" : "disabled");
    Info("REGAL_FORCE_EMU_IFF       ", forceEmuIff      ? "enabled" : "disabled");
    Info("REGAL_FORCE_EMU_SO        ", forceEmuSo       ? "enabled" : "disabled");
    Info("REGAL_FORCE_EMU_VAO       ", forceEmuVao      ? "enabled" : "disabled");
    Info("REGAL_FORCE_EMU_FILTER    ", forceEmuFilter   ? "enabled" : "disabled");
    Info("REGAL_FORCE_EMU_TEXC      ", forceEmuTexC     ? "enabled" : "disabled");

    Info("REGAL_FRAME_LIMIT         ", frameLimit                               );

    Info("REGAL_MD5_COLOR           ", frameMd5Color    ? "enabled" : "disabled");
    Info("REGAL_MD5_STENCIL         ", frameMd5Stencil  ? "enabled" : "disabled");
    Info("REGAL_MD5_DEPTH           ", frameMd5Depth    ? "enabled" : "disabled");

    Info("REGAL_SAVE_COLOR          ", frameSaveColor   ? "enabled" : "disabled");
    Info("REGAL_SAVE_STENCIL        ", frameSaveStencil ? "enabled" : "disabled");
    Info("REGAL_SAVE_DEPTH          ", frameSaveDepth   ? "enabled" : "disabled");

#if REGAL_CACHE
    Info("REGAL_CACHE               ", cache             ? "enabled" : "disabled");
    Info("REGAL_CACHE_TEXTURE       ", cacheTexture      ? "enabled" : "disabled");
    Info("REGAL_CACHE_TEXTURE_WRITE ", cacheTextureWrite ? "enabled" : "disabled");
#endif

#if REGAL_CODE
    Info("REGAL_CODE_SOURCE         ", codeSourceFile                            );
    Info("REGAL_CODE_HEADER         ", codeHeaderFile                            );
#endif

    Info("REGAL_THREAD_LOCKING      ", enableThreadLocking ? "enabled" : "disabled");
  }