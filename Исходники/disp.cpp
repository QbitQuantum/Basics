// Create the primary surface
static int MakePrimarySurface()
{
  int Ret=0; unsigned int PrimFormat=0; int PrimBpp=0;
  DDSURFACEDESC ddsd;
  DispPrim=NULL;
  memset(&ddsd,0,sizeof(ddsd));
  ddsd.dwSize=sizeof(ddsd);
  ddsd.dwFlags=DDSD_CAPS;
  ddsd.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE;
  Ret=pDD->CreateSurface(&ddsd,&DispPrim,NULL);
  if (Ret<0) return 1; if (DispPrim==NULL) return 1; 

  // Find out the color to use to paint the overlay
  GetSurfaceFormat(DispPrim,&PrimFormat,&PrimBpp);
  switch (PrimFormat)
  {
    default: OverlayColor=0; break;
    case 15: OverlayColor=0x0401; break;
    case 16: OverlayColor=0x0801; break;
    case 24: case 32: OverlayColor=0x080008; break;
  }

  // Create a clipper
  Ret=DirectDrawCreateClipper(0,&pClipper,NULL);
  if (Ret==DD_OK)
  {
    Ret=pClipper->SetHWnd(0,hFrameWnd);
    if (Ret==DD_OK) DispPrim->SetClipper(pClipper);
  }

  return 0;
}