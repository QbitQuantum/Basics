void
avx512bw_test ()
{
  unsigned int i = 25;
  __mmask32 k1 = 1 << i;

  volatile __mmask32 r = _kshiftri_mask32 (k1, i);
  if (r != 1)
    abort ();
}