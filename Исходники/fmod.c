DOUBLE
FMOD (DOUBLE x, DOUBLE y)
{
  if (isfinite (x) && isfinite (y) && y != L_(0.0))
    {
      if (x == L_(0.0))
        /* Return x, regardless of the sign of y.  */
        return x;

      {
        int negate = ((!signbit (x)) ^ (!signbit (y)));

        /* Take the absolute value of x and y.  */
        x = FABS (x);
        y = FABS (y);

        /* Trivial case that requires no computation.  */
        if (x < y)
          return (negate ? - x : x);

        {
          int yexp;
          DOUBLE ym;
          DOUBLE y1;
          DOUBLE y0;
          int k;
          DOUBLE x2;
          DOUBLE x1;
          DOUBLE x0;

          /* Write y = 2^yexp * (y1 * 2^-LIMB_BITS + y0 * 2^-(2*LIMB_BITS))
             where y1 is an integer, 2^(LIMB_BITS-1) <= y1 < 2^LIMB_BITS,
             y1 has at most LIMB_BITS bits,
             0 <= y0 < 2^LIMB_BITS,
             y0 has at most (MANT_DIG + 1) / 2 bits.  */
          ym = FREXP (y, &yexp);
          ym = ym * TWO_LIMB_BITS;
          y1 = TRUNC (ym);
          y0 = (ym - y1) * TWO_LIMB_BITS;

          /* Write
               x = 2^(yexp+(k-3)*LIMB_BITS)
                   * (x2 * 2^(2*LIMB_BITS) + x1 * 2^LIMB_BITS + x0)
             where x2, x1, x0 are each integers >= 0, < 2^LIMB_BITS.  */
          {
            int xexp;
            DOUBLE xm = FREXP (x, &xexp);
            /* Since we know x >= y, we know xexp >= yexp.  */
            xexp -= yexp;
            /* Compute k = ceil(xexp / LIMB_BITS).  */
            k = (xexp + LIMB_BITS - 1) / LIMB_BITS;
            /* Note: (k - 1) * LIMB_BITS + 1 <= xexp <= k * LIMB_BITS.  */
            /* Note: 0.5 <= xm < 1.0.  */
            xm = LDEXP (xm, xexp - (k - 1) * LIMB_BITS);
            /* Note: Now xm < 2^(xexp - (k - 1) * LIMB_BITS) <= 2^LIMB_BITS
               and xm >= 0.5 * 2^(xexp - (k - 1) * LIMB_BITS) >= 1.0
               and xm has at most MANT_DIG <= 2*LIMB_BITS+1 bits.  */
            x2 = TRUNC (xm);
            x1 = (xm - x2) * TWO_LIMB_BITS;
            /* Split off x0 from x1 later.  */
          }

          /* Test whether [x2,x1,0] >= 2^LIMB_BITS * [y1,y0].  */
          if (x2 > y1 || (x2 == y1 && x1 >= y0))
            {
              /* Subtract 2^LIMB_BITS * [y1,y0] from [x2,x1,0].  */
              x2 -= y1;
              x1 -= y0;
              if (x1 < L_(0.0))
                {
                  if (!(x2 >= L_(1.0)))
                    abort ();
                  x2 -= L_(1.0);
                  x1 += TWO_LIMB_BITS;
                }
            }

          /* Split off x0 from x1.  */
          {
            DOUBLE x1int = TRUNC (x1);
            x0 = TRUNC ((x1 - x1int) * TWO_LIMB_BITS);
            x1 = x1int;
          }

          for (; k > 0; k--)
            {
              /* Multiprecision division of the limb sequence [x2,x1,x0]
                 by [y1,y0].  */
              /* Here [x2,x1,x0] < 2^LIMB_BITS * [y1,y0].  */
              /* The first guess takes into account only [x2,x1] and [y1].

                 By Knuth's theorem, we know that
                   q* = min (floor ([x2,x1] / [y1]), 2^LIMB_BITS - 1)
                 and
                   q = floor ([x2,x1,x0] / [y1,y0])
                 are not far away:
                   q* - 2 <= q <= q* + 1.

                 Proof:
                 a) q* * y1 <= floor ([x2,x1] / [y1]) * y1 <= [x2,x1].
                    Hence
                    [x2,x1,x0] - q* * [y1,y0]
                      = 2^LIMB_BITS * ([x2,x1] - q* * [y1]) + x0 - q* * y0
                      >= x0 - q* * y0
                      >= - q* * y0
                      > - 2^(2*LIMB_BITS)
                      >= - 2 * [y1,y0]
                    So
                      [x2,x1,x0] > (q* - 2) * [y1,y0].
                 b) If q* = floor ([x2,x1] / [y1]), then
                      [x2,x1] < (q* + 1) * y1
                    Hence
                    [x2,x1,x0] - q* * [y1,y0]
                      = 2^LIMB_BITS * ([x2,x1] - q* * [y1]) + x0 - q* * y0
                      <= 2^LIMB_BITS * (y1 - 1) + x0 - q* * y0
                      <= 2^LIMB_BITS * (2^LIMB_BITS-2) + (2^LIMB_BITS-1) - 0
                      < 2^(2*LIMB_BITS)
                      <= 2 * [y1,y0]
                    So
                      [x2,x1,x0] < (q* + 2) * [y1,y0].
                    and so
                      q < q* + 2
                    which implies
                      q <= q* + 1.
                    In the other case, q* = 2^LIMB_BITS - 1.  Then trivially
                      q < 2^LIMB_BITS = q* + 1.

                 We know that floor ([x2,x1] / [y1]) >= 2^LIMB_BITS if and
                 only if x2 >= y1.  */
              DOUBLE q =
                (x2 >= y1
                 ? TWO_LIMB_BITS - L_(1.0)
                 : TRUNC ((x2 * TWO_LIMB_BITS + x1) / y1));
              if (q > L_(0.0))
                {
                  /* Compute
                     [x2,x1,x0] - q* * [y1,y0]
                       = 2^LIMB_BITS * ([x2,x1] - q* * [y1]) + x0 - q* * y0.  */
                  DOUBLE q_y1 = q * y1; /* exact, at most 2*LIMB_BITS bits */
                  DOUBLE q_y1_1 = TRUNC (q_y1 * TWO_LIMB_BITS_INVERSE);
                  DOUBLE q_y1_0 = q_y1 - q_y1_1 * TWO_LIMB_BITS;
                  DOUBLE q_y0 = q * y0; /* exact, at most MANT_DIG bits */
                  DOUBLE q_y0_1 = TRUNC (q_y0 * TWO_LIMB_BITS_INVERSE);
                  DOUBLE q_y0_0 = q_y0 - q_y0_1 * TWO_LIMB_BITS;
                  x2 -= q_y1_1;
                  x1 -= q_y1_0;
                  x1 -= q_y0_1;
                  x0 -= q_y0_0;
                  /* Move negative carry from x0 to x1 and from x1 to x2.  */
                  if (x0 < L_(0.0))
                    {
                      x0 += TWO_LIMB_BITS;
                      x1 -= L_(1.0);
                    }
                  if (x1 < L_(0.0))
                    {
                      x1 += TWO_LIMB_BITS;
                      x2 -= L_(1.0);
                      if (x1 < L_(0.0)) /* not sure this can happen */
                        {
                          x1 += TWO_LIMB_BITS;
                          x2 -= L_(1.0);
                        }
                    }
                  if (x2 < L_(0.0))
                    {
                      /* Reduce q by 1.  */
                      x1 += y1;
                      x0 += y0;
                      /* Move overflow from x0 to x1 and from x1 to x0.  */
                      if (x0 >= TWO_LIMB_BITS)
                        {
                          x0 -= TWO_LIMB_BITS;
                          x1 += L_(1.0);
                        }
                      if (x1 >= TWO_LIMB_BITS)
                        {
                          x1 -= TWO_LIMB_BITS;
                          x2 += L_(1.0);
                        }
                      if (x2 < L_(0.0))
                        {
                          /* Reduce q by 1 again.  */
                          x1 += y1;
                          x0 += y0;
                          /* Move overflow from x0 to x1 and from x1 to x0.  */
                          if (x0 >= TWO_LIMB_BITS)
                            {
                              x0 -= TWO_LIMB_BITS;
                              x1 += L_(1.0);
                            }
                          if (x1 >= TWO_LIMB_BITS)
                            {
                              x1 -= TWO_LIMB_BITS;
                              x2 += L_(1.0);
                            }
                          if (x2 < L_(0.0))
                            /* Shouldn't happen, because we proved that
                               q >= q* - 2.  */
                            abort ();
                        }
                    }
                }
              if (x2 > L_(0.0)
                  || x1 > y1
                  || (x1 == y1 && x0 >= y0))
                {
                  /* Increase q by 1.  */
                  x1 -= y1;
                  x0 -= y0;
                  /* Move negative carry from x0 to x1 and from x1 to x2.  */
                  if (x0 < L_(0.0))
                    {
                      x0 += TWO_LIMB_BITS;
                      x1 -= L_(1.0);
                    }
                  if (x1 < L_(0.0))
                    {
                      x1 += TWO_LIMB_BITS;
                      x2 -= L_(1.0);
                    }
                  if (x2 < L_(0.0))
                    abort ();
                  if (x2 > L_(0.0)
                      || x1 > y1
                      || (x1 == y1 && x0 >= y0))
                    /* Shouldn't happen, because we proved that
                       q <= q* + 1.  */
                    abort ();
                }
              /* Here [x2,x1,x0] < [y1,y0].  */
              /* Next round.  */
              x2 = x1;
#if (MANT_DIG + 1) / 2 > LIMB_BITS /* y0 can have a fractional bit */
              x1 = TRUNC (x0);
              x0 = (x0 - x1) * TWO_LIMB_BITS;
#else
              x1 = x0;
              x0 = L_(0.0);
#endif
              /* Here [x2,x1,x0] < 2^LIMB_BITS * [y1,y0].  */
            }
          /* Here k = 0.
             The result is
               2^(yexp-3*LIMB_BITS)
               * (x2 * 2^(2*LIMB_BITS) + x1 * 2^LIMB_BITS + x0).  */
          {
            DOUBLE r =
              LDEXP ((x2 * TWO_LIMB_BITS + x1) * TWO_LIMB_BITS + x0,
                     yexp - 3 * LIMB_BITS);
            return (negate ? - r : r);
          }
        }
      }
    }
  else
    {
      if (ISNAN (x) || ISNAN (y))
        return x + y; /* NaN */
      else if (isinf (y))
        return x;
      else
        /* x infinite or y zero */
        return NAN;
    }
}