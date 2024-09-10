inline T Clamp(const T x, const T xMin, const T xMax)
{
  return Max(xMin, Min(x, xMax));
}