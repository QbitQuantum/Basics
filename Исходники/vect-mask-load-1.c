__attribute__((noinline, noclone)) void
foo (double *x, double *y)
{
  double *p = __builtin_assume_aligned (x, 16);
  double *q = __builtin_assume_aligned (y, 16);
  double z, h;
  int i;
  for (i = 0; i < 1024; i++)
    {
      if (p[i] < 0.0)
	z = q[i], h = q[i] * 7.0 + 3.0;
      else
	z = p[i] + 6.0, h = p[1024 + i];
      p[i] = z + 2.0 * h;
    }
}