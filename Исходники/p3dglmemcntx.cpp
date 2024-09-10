bool               P3DGLMemoryContextPBuffer::Create
                                      (unsigned int        Width,
                                       unsigned int        Height,
                                       bool                NeedAlpha)
 {
  int              PixelFormat;
  UINT             FormatCount;
  HDC              CurrDeviceContext;

  CurrDeviceContext = wglGetCurrentDC();

  if (wglChoosePixelFormatARB( CurrDeviceContext,
                               NeedAlpha ? PBufferPixelFormatIntAttrsAlpha :
                                           PBufferPixelFormatIntAttrsNoAlpha,
                               NULL,
                               1,
                              &PixelFormat,
                              &FormatCount))
   {
    if (FormatCount == 0)
     {
      return(false);
     }
   }
  else
   {
    return(false);
   }

  PBufferHandle = wglCreatePbufferARB
                   (CurrDeviceContext,
                    PixelFormat, 
                    Width,
                    Height,
                    PBufferAttrs);

  if (PBufferHandle == NULL)
   {
    return(false);
   }

  PBufferDC = wglGetPbufferDCARB(PBufferHandle);
  GLContext = wglCreateContext(PBufferDC);

  if (MakeCurrent())
   {
    return(P3DGLExtInit());
   }
  else
   {
    return(false);
   }

  return(true);
 }