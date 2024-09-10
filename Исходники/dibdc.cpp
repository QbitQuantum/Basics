//
// Stretches the DIB onto the destination DC.
//
bool
TDibDC::StretchBltToScreen(TDC& dstDC, const TRect& dst, const TRect& src) const
{
  return dstDC.StretchBlt(dst, *this, src);
}