DOUBLE
FUNC (DOUBLE x, int *expptr)
{
  int exponent;
  DECL_ROUNDING

  BEGIN_ROUNDING ();

#ifdef USE_FREXP_LDEXP
  /* frexp and ldexp are usually faster than the loop below.  */
  x = FREXP (x, &exponent);

  x = x + x;
  exponent -= 1;

  if (exponent < MIN_EXP - 1)
    {
      x = LDEXP (x, exponent - (MIN_EXP - 1));
      exponent = MIN_EXP - 1;
    }
#else
  {
    /* Since the exponent is an 'int', it fits in 64 bits.  Therefore the
       loops are executed no more than 64 times.  */
    DOUBLE pow2[64]; /* pow2[i] = 2^2^i */
    DOUBLE powh[64]; /* powh[i] = 2^-2^i */
    int i;

    exponent = 0;
    if (x >= L_(1.0))
      {
        /* A nonnegative exponent.  */
        {
          DOUBLE pow2_i; /* = pow2[i] */
          DOUBLE powh_i; /* = powh[i] */

          /* Invariants: pow2_i = 2^2^i, powh_i = 2^-2^i,
             x * 2^exponent = argument, x >= 1.0.  */
          for (i = 0, pow2_i = L_(2.0), powh_i = L_(0.5);
               ;
               i++, pow2_i = pow2_i * pow2_i, powh_i = powh_i * powh_i)
            {
              if (x >= pow2_i)
                {
                  exponent += (1 << i);
                  x *= powh_i;
                }
              else
                break;

              pow2[i] = pow2_i;
              powh[i] = powh_i;
            }
        }
        /* Here 1.0 <= x < 2^2^i.  */
      }
    else
      {
        /* A negative exponent.  */
        {
          DOUBLE pow2_i; /* = pow2[i] */
          DOUBLE powh_i; /* = powh[i] */

          /* Invariants: pow2_i = 2^2^i, powh_i = 2^-2^i,
             x * 2^exponent = argument, x < 1.0, exponent >= MIN_EXP - 1.  */
          for (i = 0, pow2_i = L_(2.0), powh_i = L_(0.5);
               ;
               i++, pow2_i = pow2_i * pow2_i, powh_i = powh_i * powh_i)
            {
              if (exponent - (1 << i) < MIN_EXP - 1)
                break;

              exponent -= (1 << i);
              x *= pow2_i;
              if (x >= L_(1.0))
                break;

              pow2[i] = pow2_i;
              powh[i] = powh_i;
            }
        }
        /* Here either x < 1.0 and exponent - 2^i < MIN_EXP - 1 <= exponent,
           or 1.0 <= x < 2^2^i and exponent >= MIN_EXP - 1.  */

        if (x < L_(1.0))
          /* Invariants: x * 2^exponent = argument, x < 1.0 and
             exponent - 2^i < MIN_EXP - 1 <= exponent.  */
          while (i > 0)
            {
              i--;
              if (exponent - (1 << i) >= MIN_EXP - 1)
                {
                  exponent -= (1 << i);
                  x *= pow2[i];
                  if (x >= L_(1.0))
                    break;
                }
            }

        /* Here either x < 1.0 and exponent = MIN_EXP - 1,
           or 1.0 <= x < 2^2^i and exponent >= MIN_EXP - 1.  */
      }

    /* Invariants: x * 2^exponent = argument, and
       either x < 1.0 and exponent = MIN_EXP - 1,
       or 1.0 <= x < 2^2^i and exponent >= MIN_EXP - 1.  */
    while (i > 0)
      {
        i--;
        if (x >= pow2[i])
          {
            exponent += (1 << i);
            x *= powh[i];
          }
      }
    /* Here either x < 1.0 and exponent = MIN_EXP - 1,
       or 1.0 <= x < 2.0 and exponent >= MIN_EXP - 1.  */
  }
#endif

  END_ROUNDING ();

  *expptr = exponent;
  return x;
}