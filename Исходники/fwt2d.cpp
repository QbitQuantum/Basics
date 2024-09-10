static long ilog2(unsigned long x)
{
  int   p;
  float v = frexpf((float)x, &p);
  return (v > 0.5 ? p : p-1);
}