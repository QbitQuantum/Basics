GFC_REAL_16
nearest_r16 (GFC_REAL_16 s, GFC_REAL_16 dir)
{
  dir = copysignl (__builtin_infl (), dir);
  if (FLT_EVAL_METHOD != 0)
    {
      /* ??? Work around glibc bug on x86.  */
      volatile GFC_REAL_16 r = nextafterl (s, dir);
      return r;
    }
  else
    return nextafterl (s, dir);
}