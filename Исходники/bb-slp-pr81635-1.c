void
f4 (double *p, double *q)
{
  p = (double *) __builtin_assume_aligned (p, sizeof (double) * 2);
  q = (double *) __builtin_assume_aligned (q, sizeof (double) * 2);
  for (unsigned int i = 0; i < 500; i += 6)
    for (unsigned int j = 0; j < 500; j += 4)
      {
	double a = q[j] + p[i];
	double b = q[j + 1] + p[i + 1];
	q[i] = a;
	q[i + 1] = b;
      }
}