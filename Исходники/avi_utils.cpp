HRESULT SetAviVideoCompression(HAVI avi, HBITMAP hbm, AVICOMPRESSOPTIONS *opts, bool ShowDialog, HWND hparent)
{ if (avi==NULL) return AVIERR_BADHANDLE;
  if (hbm==NULL) return AVIERR_BADPARAM;
  DIBSECTION dibs; int sbm = GetObject(hbm,sizeof(dibs),&dibs);
  if (sbm!=sizeof(DIBSECTION)) return AVIERR_BADPARAM;
  TAviUtil *au = (TAviUtil*)avi;
  if (au->iserr) return AVIERR_ERROR;
  if (au->psCompressed!=0) return AVIERR_COMPRESSOR;
  //
  if (au->ps==0) // create the stream, if it wasn't there before
  { AVISTREAMINFO strhdr; ZeroMemory(&strhdr,sizeof(strhdr));
    strhdr.fccType = streamtypeVIDEO;// stream type
    strhdr.fccHandler = 0; 
    strhdr.dwScale = au->period;
    strhdr.dwRate = 1000;
    strhdr.dwSuggestedBufferSize  = dibs.dsBmih.biSizeImage;
    SetRect(&strhdr.rcFrame, 0, 0, dibs.dsBmih.biWidth, dibs.dsBmih.biHeight);
    HRESULT hr=AVIFileCreateStream(au->pfile, &au->ps, &strhdr);
    if (hr!=AVIERR_OK) {au->iserr=true; return hr;}
  }
  //
  if (au->psCompressed==0) // set the compression, prompting dialog if necessary
  { AVICOMPRESSOPTIONS myopts; ZeroMemory(&myopts,sizeof(myopts));
    AVICOMPRESSOPTIONS *aopts[1];
    if (opts!=NULL) aopts[0]=opts; else aopts[0]=&myopts;
    if (ShowDialog)
    { BOOL res = (BOOL)AVISaveOptions(hparent,0,1,&au->ps,aopts);
      if (!res) {AVISaveOptionsFree(1,aopts); au->iserr=true; return AVIERR_USERABORT;}
    }
    HRESULT hr = AVIMakeCompressedStream(&au->psCompressed, au->ps, aopts[0], NULL);
    AVISaveOptionsFree(1,aopts);
    if (hr != AVIERR_OK) {au->iserr=true; return hr;}
    DIBSECTION dibs; GetObject(hbm,sizeof(dibs),&dibs);
    hr = AVIStreamSetFormat(au->psCompressed, 0, &dibs.dsBmih, dibs.dsBmih.biSize+dibs.dsBmih.biClrUsed*sizeof(RGBQUAD));
    if (hr!=AVIERR_OK) {au->iserr=true; return hr;}
  }
  //
  return AVIERR_OK;
}