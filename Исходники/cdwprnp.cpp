/* 
%F cdKillCanvas para Printer.
Termina a pagina e termina o documento, enviando-o para a impressora.
*/
static void cdkillcanvas (cdCtxCanvas* ctxcanvas)
{
  cdwpKillCanvas(ctxcanvas);
  
  EndPage(ctxcanvas->hDC);
  EndDoc(ctxcanvas->hDC);

  ClosePrinter(ctxcanvas->printerHandle);
  DeleteDC(ctxcanvas->hDC);
  
  delete ctxcanvas;
}