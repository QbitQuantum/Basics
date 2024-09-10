void
test (void)
{
  TEST (acos (d), LARGE_EDOM);
  TEST (asin (d), LARGE_EDOM);
  TEST (acosh (d), LARGE_NEG_EDOM);
  TEST (atanh (d), LARGE_EDOM);
  TEST (cosh (d), LARGE_ERANGE);
  TEST (sinh (d), LARGE_ERANGE);
  TEST (log (d), LARGE_NEG_EDOM);
#if defined (__sun__) && defined (__unix__)
  /* Disabled due to a bug in Solaris libm.  */
  if (0)
#endif
    TEST (log2 (d), LARGE_NEG_EDOM);
  TEST (log10 (d), LARGE_NEG_EDOM);
  /* Disabled due to glibc PR 6792, fixed in Apr 2015.  */
  if (0)
    TEST (log1p (d), LARGE_NEG_EDOM);
  TEST (exp (d), POWER_ERANGE);
#if (defined (__sun__) || defined(__hppa__)) && defined (__unix__)
  /* Disabled due to a bug in Solaris libm.  HP PA-RISC libm doesn't support
     ERANGE for exp2.  */
  if (0)
#endif
    {
      TEST (exp2 (d), POWER_ERANGE);
      TEST (expm1 (d), POWER_ERANGE);
    }
  TEST (sqrt (d), LARGE_NEG_EDOM);
  TEST (pow (100.0, d), POWER_ERANGE);
  TEST (pow (i, d), POWER_ERANGE);
}