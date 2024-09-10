static void cdflush(cdCtxCanvas *ctxcanvas)
{
  fflush(ctxcanvas->file);
  fprintf(ctxcanvas->file, "%d\n", CDMF_FLUSH);
}