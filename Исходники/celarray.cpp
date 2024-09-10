//
/// Draws the image of the cel onto the DC.
//
bool
TCelArray::StretchBlt(int index, TDC& dstDC, const TRect& dstRect, uint32 rop)
{
  TMemoryDC srcDC(*Bitmap);
  TRect cr = CelRect(index,-1);
  dstDC.StretchBlt(dstRect.left,dstRect.top, dstRect.Width(),dstRect.Height(),
                   srcDC, cr.left, cr.top, cr.Width(), cr.Height(), rop);
  return true;
}