int
main (void)
{
  long double x;
  int y;
  for (y = 0; y < 29; y++)
    printf ("%5d %.16Lg %.16Lg\n", y, ldexpl (0.8L, y), ldexpl (0.8L, -y) * ldexpl (0.8L, y));
}