GLX::~GLX()
{
  if (mDisplay) {
    MakeCurrent(mDisplay, 0, 0);
  }

  if (mContext) {
    DestroyContext(mDisplay, mContext);
  }

  if (mGLXPixmap) {
    DestroyGLXPixmap(mDisplay, mGLXPixmap);
  }

  if (mPixmap) {
    XFreePixmap(mDisplay, mPixmap);
  }

  if (mDisplay) {
    XCloseDisplay(mDisplay);
  }

  if (mLibGL) {
    dlclose(mLibGL);
  }
}