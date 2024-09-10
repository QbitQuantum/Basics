int IupGLIsCurrent (Ihandle* self)
{
  GLData* d = (GLData*)IupGetAttribute(self,"_IUPGL_DATA"); 
  if (d)
  {
    if (d->context == wglGetCurrentContext())
      return 1;
  }
  return 0;
}