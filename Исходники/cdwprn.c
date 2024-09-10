/* 
%F cdFlush para Printer.
Termina uma pagina e inicia outra.
*/
static void cdflush(cdCtxCanvas *ctxcanvas)
{
  GdiFlush();
  EndPage(ctxcanvas->hDC);

  StartPage(ctxcanvas->hDC);
  cdwRestoreDC(ctxcanvas);
}