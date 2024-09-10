/*************************************************************************
 * trio_isinf
 */
TRIO_PUBLIC int
trio_isinf(TRIO_VOLATILE double number)
{
#if defined(TRIO_COMPILER_DECC)
  /*
   * DECC has an isinf() macro, but it works differently than that
   * of C99, so we use the fp_class() function instead.
   */
  return ((fp_class(number) == FP_POS_INF)
	  ? 1
	  : ((fp_class(number) == FP_NEG_INF) ? -1 : 0));
  
#elif defined(isinf)
  /*
   * C99 defines isinf() as a macro.
   */
  return isinf(number);
  
#elif defined(TRIO_COMPILER_MSVC)
  /*
   * MSVC has an _fpclass() function that can be used to detect infinity.
   */
  return ((_fpclass(number) == _FPCLASS_PINF)
	  ? 1
	  : ((_fpclass(number) == _FPCLASS_NINF) ? -1 : 0));

#elif defined(USE_IEEE_754)
  /*
   * Examine IEEE 754 bit-pattern. Infinity must have a special exponent
   * pattern, and an empty mantissa.
   */
  int has_mantissa;
  int is_special_quantity;

  is_special_quantity = trio_is_special_quantity(number, &has_mantissa);
  
  return (is_special_quantity && !has_mantissa)
    ? ((number < 0.0) ? -1 : 1)
    : 0;

#else
  /*
   * Fallback solution.
   */
  int status;
  
# if defined(TRIO_PLATFORM_UNIX)
  void (*signal_handler)(int) = signal(SIGFPE, SIG_IGN);
# endif
  
  double infinity = trio_pinf();
  
  status = ((number == infinity)
	    ? 1
	    : ((number == -infinity) ? -1 : 0));
  
# if defined(TRIO_PLATFORM_UNIX)
  signal(SIGFPE, signal_handler);
# endif
  
  return status;
  
#endif
}