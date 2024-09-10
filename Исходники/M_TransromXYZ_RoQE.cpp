//===========================================================================
void TTransromXYZ_RoQE::DrawElementFace()
{
      TCanvas    *dbCanvas = VisualElementParam->Bitmap->Canvas;
      int         aw       = VisualElementParam->Width ;
      int         ah       = VisualElementParam->Height;

      dbCanvas->Brush->Color = clWhite;
      dbCanvas->Pen  ->Color = clBlack;

      dbCanvas->Rectangle(0, 0, aw, ah);

   // --------- Отрисовка прямоугольника --- (прямокгольник процесса разработки) -----
     if (DesignPhase != dpAllreadyTesting) {
         if (DesignPhase == dpNotTesting  ) {dbCanvas->Pen  ->Color = clRed;}
         if (DesignPhase == dpNeedModified) {dbCanvas->Pen  ->Color = clRed; dbCanvas->Pen  ->Style = psDot;}

         dbCanvas->Rectangle(2, 2, VisualElementParam->Width - 2, VisualElementParam->Height - 2);

         dbCanvas->Pen->Color = clBlack;
         dbCanvas->Pen->Style = psSolid;
      }   

      dbCanvas->MoveTo(5, 2     );   dbCanvas->LineTo(5, ah - 2);
      dbCanvas->MoveTo(2, ah - 5);   dbCanvas->LineTo(aw - 2, ah - 5);

      dbCanvas->Pen->Color = clBlue;
      dbCanvas->MoveTo(8, ah - 10);   dbCanvas->LineTo(aw - 4, 6);

      dbCanvas->Pen->Color = clBlack;
}