void
FC_FUNC_(force_ftz,FORCE_FTZ)()
{
#ifdef FORCE_FTZ
  unsigned int x;

  /* force FTZ by setting bits 11 and 15 to one */
  x = _mm_getcsr();
  x |= (1 << FTZ_BIT);
  x |= (1 << UNDERFLOW_EXCEPTION_MASK);
  _mm_setcsr(x);
#endif
}