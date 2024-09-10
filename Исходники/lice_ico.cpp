static LICE_IBitmap *icoToBitmap(HICON icon, LICE_IBitmap *bmpOut)
{
  int icon_w = 16, icon_h=16;

#ifdef _WIN32
  ICONINFO ii={0,};
  if (GetIconInfo(icon,&ii))
  {
    bool blah=false;
    if (ii.hbmColor)
    {
      BITMAP bm={0,};
      if (GetObject(ii.hbmColor,sizeof(bm),&bm) && bm.bmWidth && bm.bmHeight)
      {
        icon_w=bm.bmWidth;
        icon_h=bm.bmHeight;
        blah=true;
      }
      DeleteObject(ii.hbmColor);
    }
    if (ii.hbmMask)
    {
      BITMAP bm={0,};
      if (!blah && GetObject(ii.hbmMask,sizeof(bm),&bm) && bm.bmWidth && bm.bmHeight)
      {
        icon_w=bm.bmWidth;
        icon_h=bm.bmHeight;
      }
      DeleteObject(ii.hbmMask);
    }
  }
#else
  BITMAP bm={0,};
  if (GetObject(icon,sizeof(bm),&bm) && bm.bmWidth && bm.bmHeight) // SWELL's GetObject() works on icons
  {
    icon_w=bm.bmWidth;
    icon_h=bm.bmHeight;
  }

#endif

  LICE_SysBitmap tempbm(icon_w*2,icon_h);
  LICE_FillRect(&tempbm,0,0,icon_w,icon_h,LICE_RGBA(0,0,0,255),1.0f,LICE_BLIT_MODE_COPY);
#ifdef _WIN32
  DrawIconEx(tempbm.getDC(),0,0,icon,icon_w,icon_h,0,NULL,DI_NORMAL);
#else
  {
    RECT r={0,0,icon_w,icon_h};
    DrawImageInRect(tempbm.getDC(),icon,&r);
  }
#endif

  LICE_FillRect(&tempbm,icon_w,0,icon_w,icon_h,LICE_RGBA(255,255,255,255),1.0f,LICE_BLIT_MODE_COPY);
#ifdef _WIN32
  DrawIconEx(tempbm.getDC(),icon_w,0,icon,icon_w,icon_h,0,NULL,DI_NORMAL);
#else
  {
    RECT r={icon_w,0,icon_w+icon_w,icon_h};
    DrawImageInRect(tempbm.getDC(),icon,&r);
  }
#endif

  if (!bmpOut) bmpOut = new LICE_MemBitmap(icon_w,icon_h);
  else bmpOut->resize(icon_w,icon_h);

  int y; // since we have the image drawn on white and on black, we can calculate the alpha channel...
  for(y=0;y<icon_h;y++)
  {
    int x;
    for(x=0;x<icon_w;x++)
    {
      LICE_pixel p = LICE_GetPixel(&tempbm,x,y);
      LICE_pixel p2 = LICE_GetPixel(&tempbm,x+icon_w,y);

      int r1=LICE_GETR(p);
      int g1=LICE_GETG(p);
      int b1=LICE_GETB(p);

      int alpha=255 - (LICE_GETR(p2)-r1);
      if (alpha>=255) alpha=255;
      else if (alpha>0)
      {
        r1 = (r1*255)/alpha; // LICE stores its alpha channel non-premultiplied, so we need to scale these up.
        g1 = (g1*255)/alpha;
        b1 = (b1*255)/alpha;
        if (r1>255)r1=255;
        if (g1>255)g1=255;
        if (b1>255)b1=255;
      }
      else alpha=0;
      LICE_PutPixel(bmpOut,x,y,LICE_RGBA(r1,g1,b1,alpha),1.0f,LICE_BLIT_MODE_COPY);
    }
  }

  return bmpOut;
}