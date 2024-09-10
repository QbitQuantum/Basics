static void cdkillcanvas(cdCtxCanvas *ctxcanvas)
{
  HMETAFILE hmf;
  
  cdwKillCanvas(ctxcanvas);
  
  hmf = CloseMetaFile(ctxcanvas->hDC);
  wmfMakePlaceableMetafile(hmf, ctxcanvas->filename, ctxcanvas->canvas->w, ctxcanvas->canvas->h);
  DeleteMetaFile(hmf);

  free(ctxcanvas->filename);
  
  memset(ctxcanvas, 0, sizeof(cdCtxCanvas));
  free(ctxcanvas);
}