static inline int fftw_2N_rev(int n)
{
  return (LRINT(K(0.5) * n) + 1);
}