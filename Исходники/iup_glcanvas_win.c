static int wGLCreateContext(Ihandle* ih, IGlControlData* gldata)
{
  Ihandle* ih_shared;
  HGLRC shared_context = NULL;
  int number;
  int isIndex = 0;
  int pixelFormat;
  PIXELFORMATDESCRIPTOR test_pfd;
  PIXELFORMATDESCRIPTOR pfd = { 
    sizeof(PIXELFORMATDESCRIPTOR),  /*  size of this pfd   */
      1,                     /* version number             */
      PFD_DRAW_TO_WINDOW |   /* support window             */
      PFD_SUPPORT_OPENGL,    /* support OpenGL             */
      PFD_TYPE_RGBA,         /* RGBA type                  */
      24,                    /* 24-bit color depth         */
      0, 0, 0, 0, 0, 0,      /* color bits ignored         */
      0,                     /* no alpha buffer            */
      0,                     /* shift bit ignored          */
      0,                     /* no accumulation buffer     */
      0, 0, 0, 0,            /* accum bits ignored         */
      16,                    /* 32-bit z-buffer             */
      0,                     /* no stencil buffer          */
      0,                     /* no auxiliary buffer        */
      PFD_MAIN_PLANE,        /* main layer                 */
      0,                     /* reserved                   */
      0, 0, 0                /* layer masks ignored        */
  };

  /* the IupCanvas is already mapped, just initialize the OpenGL context */

  /* double or single buffer */
  if (iupStrEqualNoCase(iupAttribGetStr(ih,"BUFFER"), "DOUBLE"))
    pfd.dwFlags |= PFD_DOUBLEBUFFER;

  /* stereo */
  if (iupAttribGetBoolean(ih,"STEREO"))
    pfd.dwFlags |= PFD_STEREO;

  /* rgba or index */ 
  if (iupStrEqualNoCase(iupAttribGetStr(ih,"COLOR"), "INDEX"))
  {
    isIndex = 1;
    pfd.iPixelType = PFD_TYPE_COLORINDEX;
    pfd.cColorBits = 8;  /* assume 8 bits when indexed */
    number = iupAttribGetInt(ih,"BUFFER_SIZE");
    if (number > 0) pfd.cColorBits = (BYTE)number;
  }

  /* red, green, blue bits */
  number = iupAttribGetInt(ih,"RED_SIZE");
  if (number > 0) pfd.cRedBits = (BYTE)number;
  pfd.cRedShift = 0;

  number = iupAttribGetInt(ih,"GREEN_SIZE");
  if (number > 0) pfd.cGreenBits = (BYTE)number;
  pfd.cGreenShift = pfd.cRedBits;

  number = iupAttribGetInt(ih,"BLUE_SIZE");
  if (number > 0) pfd.cBlueBits = (BYTE)number;
  pfd.cBlueShift = pfd.cRedBits + pfd.cGreenBits;

  number = iupAttribGetInt(ih,"ALPHA_SIZE");
  if (number > 0) pfd.cAlphaBits = (BYTE)number;
  pfd.cAlphaShift = pfd.cRedBits + pfd.cGreenBits + pfd.cBlueBits;

  /* depth and stencil size */
  number = iupAttribGetInt(ih,"DEPTH_SIZE");
  if (number > 0) pfd.cDepthBits = (BYTE)number;

  /* stencil */
  number = iupAttribGetInt(ih,"STENCIL_SIZE");
  if (number > 0) pfd.cStencilBits = (BYTE)number;

  /* red, green, blue accumulation bits */
  number = iupAttribGetInt(ih,"ACCUM_RED_SIZE");
  if (number > 0) pfd.cAccumRedBits = (BYTE)number;

  number = iupAttribGetInt(ih,"ACCUM_GREEN_SIZE");
  if (number > 0) pfd.cAccumGreenBits = (BYTE)number;

  number = iupAttribGetInt(ih,"ACCUM_BLUE_SIZE");
  if (number > 0) pfd.cAccumBlueBits = (BYTE)number;

  number = iupAttribGetInt(ih,"ACCUM_ALPHA_SIZE");
  if (number > 0) pfd.cAccumAlphaBits = (BYTE)number;

  pfd.cAccumBits = pfd.cAccumRedBits + pfd.cAccumGreenBits + pfd.cAccumBlueBits + pfd.cAccumAlphaBits;

  /* get a device context */
  {
    LONG style = GetClassLong(gldata->window, GCL_STYLE);
    gldata->is_owned_dc = (int) ((style & CS_OWNDC) || (style & CS_CLASSDC));
  }

  gldata->device = GetDC(gldata->window);
  iupAttribSet(ih, "VISUAL", (char*)gldata->device);

  /* choose pixel format */
  pixelFormat = ChoosePixelFormat(gldata->device, &pfd);
  if (pixelFormat == 0)
  {
    iupAttribSet(ih, "ERROR", "No appropriate pixel format.");
    iupAttribSetStr(ih, "LASTERROR", IupGetGlobal("LASTERROR"));
    return IUP_NOERROR;
  } 
  SetPixelFormat(gldata->device,pixelFormat,&pfd);

  ih_shared = IupGetAttributeHandle(ih, "SHAREDCONTEXT");
  if (ih_shared && IupClassMatch(ih_shared, "glcanvas"))  /* must be an IupGLCanvas */
  {
    IGlControlData* shared_gldata = (IGlControlData*)iupAttribGet(ih_shared, "_IUP_GLCONTROLDATA");
    shared_context = shared_gldata->context;
  }

  /* create rendering context */
  if (iupAttribGetBoolean(ih, "ARBCONTEXT"))
  {
    wglCreateContextAttribsARB_PROC CreateContextAttribsARB;
    HGLRC tempContext = wglCreateContext(gldata->device);
    HGLRC oldContext = wglGetCurrentContext();
    HDC oldDC = wglGetCurrentDC();
    wglMakeCurrent(gldata->device, tempContext);   /* wglGetProcAddress only works with an active context */

    CreateContextAttribsARB = (wglCreateContextAttribsARB_PROC)wglGetProcAddress("wglCreateContextAttribsARB");
    if (CreateContextAttribsARB)
    {
      int attribs[9], a = 0;
      char* value;

      value = iupAttribGetStr(ih, "CONTEXTVERSION");
      if (value)
      {
        int major, minor;
        if (iupStrToIntInt(value, &major, &minor, '.') == 2)
        {
          attribs[a++] = WGL_CONTEXT_MAJOR_VERSION_ARB;
          attribs[a++] = major;
          attribs[a++] = WGL_CONTEXT_MINOR_VERSION_ARB;
          attribs[a++] = minor;
        }
      }

      value = iupAttribGetStr(ih, "CONTEXTFLAGS");
      if (value)
      {
        int flags = 0;
        if (iupStrEqualNoCase(value, "DEBUG"))
          flags = WGL_CONTEXT_DEBUG_BIT_ARB;
        else if (iupStrEqualNoCase(value, "FORWARDCOMPATIBLE"))
          flags = WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
        else if (iupStrEqualNoCase(value, "DEBUGFORWARDCOMPATIBLE"))
          flags = WGL_CONTEXT_DEBUG_BIT_ARB|WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
        if (flags)
        {
          attribs[a++] = WGL_CONTEXT_FLAGS_ARB;
          attribs[a++] = flags;
        }
      }

      value = iupAttribGetStr(ih, "CONTEXTPROFILE");
      if (value)
      {
        int profile = 0;
        if (iupStrEqualNoCase(value, "CORE"))
          profile = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
        else if (iupStrEqualNoCase(value, "COMPATIBILITY"))
          profile = WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
        else if (iupStrEqualNoCase(value, "CORECOMPATIBILITY"))
          profile = WGL_CONTEXT_CORE_PROFILE_BIT_ARB|WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
        if (profile)
        {
          attribs[a++] = WGL_CONTEXT_PROFILE_MASK_ARB;
          attribs[a++] = profile;
        }
      }

      attribs[a] = 0; /* terminator */

      gldata->context = CreateContextAttribsARB(gldata->device, shared_context, attribs);
      if (!gldata->context)
      {
        DWORD error = GetLastError();
        if (error == ERROR_INVALID_VERSION_ARB)
          iupAttribSetStr(ih, "LASTERROR", "Invalid ARB Version");
        else if (error == ERROR_INVALID_PROFILE_ARB)
          iupAttribSetStr(ih, "LASTERROR", "Invalid ARGB Profile");
        else
          iupAttribSetStr(ih, "LASTERROR", IupGetGlobal("LASTERROR"));

        iupAttribSet(ih, "ERROR", "Could not create a rendering context.");

        wglMakeCurrent(oldDC, oldContext);
        wglDeleteContext(tempContext);

        return IUP_NOERROR;
      }
    }

    wglMakeCurrent(oldDC, oldContext);
    wglDeleteContext(tempContext);

    if (!CreateContextAttribsARB)
    {
      gldata->context = wglCreateContext(gldata->device);
      iupAttribSet(ih, "ARBCONTEXT", "NO");
    }
  }
  else
    gldata->context = wglCreateContext(gldata->device);

  if (!gldata->context)
  {
    iupAttribSet(ih, "ERROR", "Could not create a rendering context.");
    iupAttribSetStr(ih, "LASTERROR", IupGetGlobal("LASTERROR"));
    return IUP_NOERROR;
  }

  iupAttribSet(ih, "CONTEXT", (char*)gldata->context);

  if (shared_context)
    wglShareLists(shared_context, gldata->context);

  /* create colormap for index mode */
  if (isIndex)
  {
    if (!gldata->palette)
    {
      LOGPALETTE lp = {0x300,1,{255,255,255,PC_NOCOLLAPSE}};  /* set first color as white */
      gldata->palette = CreatePalette(&lp);
      ResizePalette(gldata->palette,1<<pfd.cColorBits);
      iupAttribSet(ih, "COLORMAP", (char*)gldata->palette);
    }

    SelectPalette(gldata->device,gldata->palette,FALSE);
    RealizePalette(gldata->device);
  }

  DescribePixelFormat(gldata->device, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &test_pfd);
  if ((pfd.dwFlags & PFD_STEREO) && !(test_pfd.dwFlags & PFD_STEREO))
  {
    iupAttribSet(ih, "STEREO", "NO");
    return IUP_NOERROR;
  }

  iupAttribSet(ih, "ERROR", NULL);
  return IUP_NOERROR;
}