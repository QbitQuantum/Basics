static int colour8(double d)
{
  int i = nearbyint(255*d);

  i = MAX(i, 0);
  i = MIN(i, 255);

  return i;
}