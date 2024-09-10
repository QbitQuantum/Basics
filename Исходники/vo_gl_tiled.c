static GLint getInternalFormat(void)
{
  switch (glctx.type) {
#ifdef CONFIG_GL_WIN32
  case GLTYPE_W32:
  {
  PIXELFORMATDESCRIPTOR pfd;
  HDC vo_hdc = vo_w32_get_dc(vo_w32_window);
  int pf = GetPixelFormat(vo_hdc);
  if (!DescribePixelFormat(vo_hdc, pf, sizeof pfd, &pfd)) {
    r_sz = g_sz = b_sz = a_sz = 0;
  } else {
    r_sz = pfd.cRedBits;
    g_sz = pfd.cGreenBits;
    b_sz = pfd.cBlueBits;
    a_sz = pfd.cAlphaBits;
  }
  vo_w32_release_dc(vo_w32_window, vo_hdc);
  }
  break;
#endif
#ifdef CONFIG_GL_X11
  case GLTYPE_X11:
  if (glXGetConfig(mDisplay, glctx.vinfo.x11, GLX_RED_SIZE, &r_sz) != 0) r_sz = 0;
  if (glXGetConfig(mDisplay, glctx.vinfo.x11, GLX_GREEN_SIZE, &g_sz) != 0) g_sz = 0;
  if (glXGetConfig(mDisplay, glctx.vinfo.x11, GLX_BLUE_SIZE, &b_sz) != 0) b_sz = 0;
  if (glXGetConfig(mDisplay, glctx.vinfo.x11, GLX_ALPHA_SIZE, &a_sz) != 0) a_sz = 0;
  break;
#endif
  }

  rgb_sz=r_sz+g_sz+b_sz;
  if(rgb_sz<=0) rgb_sz=24;

#ifdef TEXTUREFORMAT_ALWAYS
  return TEXTUREFORMAT_ALWAYS;
#else
  if(r_sz==3 && g_sz==3 && b_sz==2 && a_sz==0)
    return GL_R3_G3_B2;
  if(r_sz==4 && g_sz==4 && b_sz==4 && a_sz==0)
    return GL_RGB4;
  if(r_sz==5 && g_sz==5 && b_sz==5 && a_sz==0)
    return GL_RGB5;
  if(r_sz==8 && g_sz==8 && b_sz==8 && a_sz==0)
    return GL_RGB8;
  if(r_sz==10 && g_sz==10 && b_sz==10 && a_sz==0)
    return GL_RGB10;
  if(r_sz==2 && g_sz==2 && b_sz==2 && a_sz==2)
    return GL_RGBA2;
  if(r_sz==4 && g_sz==4 && b_sz==4 && a_sz==4)
    return GL_RGBA4;
  if(r_sz==5 && g_sz==5 && b_sz==5 && a_sz==1)
    return GL_RGB5_A1;
  if(r_sz==8 && g_sz==8 && b_sz==8 && a_sz==8)
    return GL_RGBA8;
  if(r_sz==10 && g_sz==10 && b_sz==10 && a_sz==2)
    return GL_RGB10_A2;
#endif
  return GL_RGB;
}