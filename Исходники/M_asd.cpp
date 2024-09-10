//===========================================================================
void Tasd::DrawElementFace()
{
      TCanvas    *dbCanvas = VisualElementParam->Bitmap->Canvas;
      int         aw       = VisualElementParam->Width;
      int         ah       = VisualElementParam->Height;
  // --------
      int w  = 0.35 * aw;
      int h  = 0.35 * ah;
      int cx = VisualElementParam->sLeft + aw / 2;
      int cy = VisualElementParam->sTop  + ah / 2;
  // --------
      dbCanvas->Brush->Color = clWhite;
      dbCanvas->Pen  ->Color = clBlack;
  // --------
      dbCanvas->Rectangle(0, 0, aw, ah);
  // --------
      dbCanvas->Ellipse(cx - w/2, cy - h/2, cx + w/2, cy + h/2);
}