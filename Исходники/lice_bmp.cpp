LICE_IBitmap *LICE_LoadBMP(const char *filename, LICE_IBitmap *bmp) // returns a bitmap (bmp if nonzero) on success
{
  HBITMAP bm=NULL;
#ifdef _WIN32
#ifndef WDL_NO_SUPPORT_UTF8
  #ifdef WDL_SUPPORT_WIN9X
  if (GetVersion()<0x80000000)
  #endif
  {
    WCHAR wf[2048];
    if (MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,filename,-1,wf,2048))
      bm = (HBITMAP) LoadImageW(NULL,wf,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_LOADFROMFILE);
  }
#endif

  if (!bm) bm=(HBITMAP) LoadImage(NULL,filename,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_LOADFROMFILE);
#else
  bm=(HBITMAP) LoadNamedImage(filename,false);
#endif
  if (!bm) return 0;

  LICE_IBitmap *ret=hbmToBit(bm,bmp);

  DeleteObject(bm);
  return ret;
}