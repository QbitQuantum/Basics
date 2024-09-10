/* Returns 0 if the bitpattern of the \a value argument is not a valid
   floating point number, otherwise returns non-zero.

   Note that on some systems, this method will always return 0
   (i.e. false positives).
*/
int
coin_isnan(double value)
{
#ifdef HAVE_ISNAN
  return isnan(value);
#elif defined(HAVE__ISNAN)
  return _isnan(value);
#elif defined(HAVE_FPCLASS)
  if (fpclass(value) == FP_SNAN) { return 1; }
  if (fpclass(value) == FP_QNAN) { return 1; }
  return 0;
#elif defined(HAVE__FPCLASS)
  if (_fpclass(value) == _FPCLASS_SNAN) { return 1; }
  if (_fpclass(value) == _FPCLASS_QNAN) { return 1; }
  return 0;
#else
  /* FIXME: it might be possible to investigate the fp bits and decide
     in a portable manner whether or not they represent a NaN. A
     groups.google.com search turned up inconclusive. 20030919
     mortene. */
  return 0;
#endif
}