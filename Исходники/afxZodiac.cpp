void afxZodiacData::convertGradientRangeFromDegrees(Point2F& gradrange, const Point2F& gradrange_deg)
{
  F32 x = mCos(mDegToRad(gradrange_deg.x));
  F32 y = mCos(mDegToRad(gradrange_deg.y));
  if (y > x)
    gradrange.set(x, y);
  else
    gradrange.set(y, x);
}