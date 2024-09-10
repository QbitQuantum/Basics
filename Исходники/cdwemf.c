static void cdkillcanvas (cdCtxCanvas* ctxcanvas)
{
  HENHMETAFILE hmf;
  
  cdwKillCanvas(ctxcanvas);
  
  hmf = CloseEnhMetaFile(ctxcanvas->hDC);
  DeleteEnhMetaFile(hmf);
  
  memset(ctxcanvas, 0, sizeof(cdCtxCanvas));
  free(ctxcanvas);
}