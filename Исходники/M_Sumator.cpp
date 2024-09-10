//===========================================================================
void TSumator::DrawElementFace()
{
      TCanvas    *dbCanvas = VisualElementParam->Bitmap->Canvas;
      int         aw       = VisualElementParam->Width;
      int         ah       = VisualElementParam->Height;
  // --------
      int x1 = 0.35 * aw;
      int y1 = 0.32 * ah;
      int x2 = 0.35 * aw;
      int y2 = 0.50  * ah;
      int x3 = x2 + (aw - x2 - x1) / 2;
  // --------
      dbCanvas->Brush->Color = clWhite;
      dbCanvas->Pen  ->Color = clBlack;
  // --------
      dbCanvas->Rectangle(0, 0, aw, ah);
   // --------- Отрисовка прямоугольника --- (прямокгольник процесса разработки) -----
     if (DesignPhase != dpAllreadyTesting) {
         if (DesignPhase == dpNotTesting  ) {dbCanvas->Pen  ->Color = clRed;}
         if (DesignPhase == dpNeedModified) {dbCanvas->Pen  ->Color = clRed; dbCanvas->Pen  ->Style = psDot;}

         dbCanvas->Rectangle(2, 2, VisualElementParam->Width - 2, VisualElementParam->Height - 2);

         dbCanvas->Pen->Color = clBlack;
         dbCanvas->Pen->Style = psSolid;
      }   
  // --------
      dbCanvas->Pen->Width = 1;
      dbCanvas->MoveTo(aw - x1,      1.1*y1);
      dbCanvas->LineTo(aw - x1,          y1);
      dbCanvas->LineTo(x2     ,          y1);
      dbCanvas->LineTo(x3     ,          y2);
      dbCanvas->LineTo(x2     , ah -     y1);
      dbCanvas->LineTo(aw - x1, ah -     y1);
      dbCanvas->LineTo(aw - x1, ah - 1.1*y1);
      dbCanvas->Pen->Width = 1;
}