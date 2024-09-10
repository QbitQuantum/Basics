void
vector_trunc (void)
{
  int i;

  for (i = 0; i < SIZE; i++)
    a[i] = truncf (b[i]);
}