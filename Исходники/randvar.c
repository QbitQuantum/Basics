/* cumalative distribution function of a-truncated N(mean, u) */
double ighmm_rand_normal_right_cdf (double x, double mean, double u, double a)
{
# define CUR_PROC "ighmm_rand_normal_right_cdf"

  if (x <= a)
    return (0.0);
  if (u <= a) {
    GHMM_LOG(LCONVERTED, "u <= a not allowed\n");
    goto STOP;
  }
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
  /*
     Function: int erfc (double x, gsl_sf_result * result) 
     These routines compute the complementary error function
     erfc(x) = 1 - erf(x) = 2/\sqrt(\pi) \int_x^\infty \exp(-t^2). 
   */
  return 1.0 + (erf ((x - mean) / sqrt (u * 2)) -
                1.0) / erfc ((a - mean) / sqrt (u * 2));
#else
  return 1.0 + (ighmm_erf ((x - mean) / sqrt (u * 2)) -
                1.0) / ighmm_erfc ((a - mean) / sqrt (u * 2));
#endif /* Check for ISO C99 */
STOP:
  return (-1.0);
# undef CUR_PROC
}                               /* double ighmm_rand_normal_cdf */