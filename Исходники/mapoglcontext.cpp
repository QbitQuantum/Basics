bool OglContext::createPBuffer(ms_uint32 width, ms_uint32 height)
{
  HPBUFFERARB hPBuffer = NULL;
  hPBufferDC = NULL;
  hPBufferRC = NULL;

  int pixelFormat;
  int valid = false;
  UINT numFormats = 0;
  float fAttributes[] = {0,0};
  int samples = MAX_MULTISAMPLE_SAMPLES;

  while ((!valid || numFormats == 0) && samples >= 0) {
    int iAttributes[] = {
      WGL_SAMPLES_ARB,samples,
      WGL_DRAW_TO_PBUFFER_ARB,GL_TRUE,
      WGL_SUPPORT_OPENGL_ARB,GL_TRUE,
      WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB,
      WGL_COLOR_BITS_ARB,24,
      WGL_ALPHA_BITS_ARB,8,
      WGL_DEPTH_BITS_ARB,16,
      WGL_STENCIL_BITS_ARB,0,
      WGL_SAMPLE_BUFFERS_ARB,GL_TRUE,
      WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
      0,0
    };

    valid = wglChoosePixelFormatARB(window,iAttributes,fAttributes,1,&pixelFormat,&numFormats);
    if (!valid || numFormats == 0) samples -= 2;
  }

  if(numFormats == 0) {
    msSetError(MS_OGLERR, "P-buffer Error: Unable to find an acceptable pixel format.", "OglContext::createPBuffer()");
    return FALSE;
  }

  if (!(hPBuffer = wglCreatePbufferARB(window, pixelFormat, width, height, 0))) {
    msSetError(MS_OGLERR, "P-buffer Error: Unable to create P-buffer. glError: %d", "OglContext::createPBuffer()", glGetError());
    return FALSE;
  }
  if (!(hPBufferDC = wglGetPbufferDCARB(hPBuffer))) {
    msSetError(MS_OGLERR, "P-buffer Error: Unable to get P-buffer DC. glError: %d", "OglContext::createPBuffer()", glGetError());
    return FALSE;
  }
  if (!(hPBufferRC = wglCreateContext(hPBufferDC))) {
    msSetError(MS_OGLERR, "P-buffer Error: Unable to get P-buffer DC. glError: %d", "OglContext::createPBuffer()", glGetError());
    return FALSE;
  }

  if (wglShareLists(sharingContext,hPBufferRC) == FALSE) {
    msSetError(MS_OGLERR, "P-buffer Error: Unable to share display lists. glError: %d", "OglContext::createPBuffer()", glGetError());
    return FALSE;
  }

  return TRUE;
}