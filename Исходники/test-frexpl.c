int
main ()
{
  int i;
  long double x;
  DECL_LONG_DOUBLE_ROUNDING

  BEGIN_LONG_DOUBLE_ROUNDING ();

  { /* NaN.  */
    int exp = -9999;
    long double mantissa;
    x = NaNl ();
    mantissa = frexpl (x, &exp);
    ASSERT (isnanl (mantissa));
  }

  { /* Positive infinity.  */
    int exp = -9999;
    long double mantissa;
    x = 1.0L / 0.0L;
    mantissa = frexpl (x, &exp);
    ASSERT (mantissa == x);
  }

  { /* Negative infinity.  */
    int exp = -9999;
    long double mantissa;
    x = -1.0L / 0.0L;
    mantissa = frexpl (x, &exp);
    ASSERT (mantissa == x);
  }

  { /* Positive zero.  */
    int exp = -9999;
    long double mantissa;
    x = 0.0L;
    mantissa = frexpl (x, &exp);
    ASSERT (exp == 0);
    ASSERT (mantissa == x);
    ASSERT (!signbit (mantissa));
  }

  { /* Negative zero.  */
    int exp = -9999;
    long double mantissa;
    x = minus_zero;
    mantissa = frexpl (x, &exp);
    ASSERT (exp == 0);
    ASSERT (mantissa == x);
    ASSERT (signbit (mantissa));
  }

  for (i = 1, x = 1.0L; i <= LDBL_MAX_EXP; i++, x *= 2.0L)
    {
      int exp = -9999;
      long double mantissa = frexpl (x, &exp);
      ASSERT (exp == i);
      ASSERT (mantissa == 0.5L);
    }
  for (i = 1, x = 1.0L; i >= MIN_NORMAL_EXP; i--, x *= 0.5L)
    {
      int exp = -9999;
      long double mantissa = frexpl (x, &exp);
      ASSERT (exp == i);
      ASSERT (mantissa == 0.5L);
    }
  for (; i >= LDBL_MIN_EXP - 100 && x > 0.0L; i--, x *= 0.5L)
    {
      int exp = -9999;
      long double mantissa = frexpl (x, &exp);
      ASSERT (exp == i);
      ASSERT (mantissa == 0.5L);
    }

  for (i = 1, x = -1.0L; i <= LDBL_MAX_EXP; i++, x *= 2.0L)
    {
      int exp = -9999;
      long double mantissa = frexpl (x, &exp);
      ASSERT (exp == i);
      ASSERT (mantissa == -0.5L);
    }
  for (i = 1, x = -1.0L; i >= MIN_NORMAL_EXP; i--, x *= 0.5L)
    {
      int exp = -9999;
      long double mantissa = frexpl (x, &exp);
      ASSERT (exp == i);
      ASSERT (mantissa == -0.5L);
    }
  for (; i >= LDBL_MIN_EXP - 100 && x < 0.0L; i--, x *= 0.5L)
    {
      int exp = -9999;
      long double mantissa = frexpl (x, &exp);
      ASSERT (exp == i);
      ASSERT (mantissa == -0.5L);
    }

  for (i = 1, x = 1.01L; i <= LDBL_MAX_EXP; i++, x *= 2.0L)
    {
      int exp = -9999;
      long double mantissa = frexpl (x, &exp);
      ASSERT (exp == i);
      ASSERT (mantissa == 0.505L);
    }
  for (i = 1, x = 1.01L; i >= MIN_NORMAL_EXP; i--, x *= 0.5L)
    {
      int exp = -9999;
      long double mantissa = frexpl (x, &exp);
      ASSERT (exp == i);
      ASSERT (mantissa == 0.505L);
    }
  for (; i >= LDBL_MIN_EXP - 100 && x > 0.0L; i--, x *= 0.5L)
    {
      int exp = -9999;
      long double mantissa = frexpl (x, &exp);
      ASSERT (exp == i);
      ASSERT (mantissa >= 0.5L);
      ASSERT (mantissa < 1.0L);
      ASSERT (mantissa == my_ldexp (x, - exp));
    }

  for (i = 1, x = 1.73205L; i <= LDBL_MAX_EXP; i++, x *= 2.0L)
    {
      int exp = -9999;
      long double mantissa = frexpl (x, &exp);
      ASSERT (exp == i);
      ASSERT (mantissa == 0.866025L);
    }
  for (i = 1, x = 1.73205L; i >= MIN_NORMAL_EXP; i--, x *= 0.5L)
    {
      int exp = -9999;
      long double mantissa = frexpl (x, &exp);
      ASSERT (exp == i);
      ASSERT (mantissa == 0.866025L);
    }
  for (; i >= LDBL_MIN_EXP - 100 && x > 0.0L; i--, x *= 0.5L)
    {
      int exp = -9999;
      long double mantissa = frexpl (x, &exp);
      ASSERT (exp == i || exp == i + 1);
      ASSERT (mantissa >= 0.5L);
      ASSERT (mantissa < 1.0L);
      ASSERT (mantissa == my_ldexp (x, - exp));
    }

  return 0;
}