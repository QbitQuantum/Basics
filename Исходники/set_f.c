int
mpfr_set_f (mpfr_ptr y, mpf_srcptr x, mpfr_rnd_t rnd_mode)
{
  mp_limb_t *my, *mx, *tmp;
  unsigned long cnt, sx, sy;
  int inexact, carry = 0;
  MPFR_TMP_DECL(marker);

  sx = ABS(SIZ(x)); /* number of limbs of the mantissa of x */

  if (sx == 0) /* x is zero */
    {
      MPFR_SET_ZERO(y);
      MPFR_SET_POS(y);
      return 0; /* 0 is exact */
    }

  if (SIZ(x) * MPFR_FROM_SIGN_TO_INT(MPFR_SIGN(y)) < 0)
    MPFR_CHANGE_SIGN (y);

  sy = MPFR_LIMB_SIZE (y);
  my = MPFR_MANT(y);
  mx = PTR(x);

  count_leading_zeros(cnt, mx[sx - 1]);

  if (sy <= sx) /* we may have to round even when sy = sx */
    {
      unsigned long xprec = sx * GMP_NUMB_BITS;

      MPFR_TMP_MARK(marker);
      tmp = MPFR_TMP_LIMBS_ALLOC (sx);
      if (cnt)
        mpn_lshift (tmp, mx, sx, cnt);
      else
        /* FIXME: we may avoid the copy here, and directly call mpfr_round_raw
           on mx instead of tmp */
        MPN_COPY (tmp, mx, sx);
      carry = mpfr_round_raw (my, tmp, xprec, (SIZ(x) < 0), MPFR_PREC(y),
                              rnd_mode, &inexact);
      if (MPFR_UNLIKELY(carry)) /* result is a power of two */
        my[sy - 1] = MPFR_LIMB_HIGHBIT;
      MPFR_TMP_FREE(marker);
    }
  else
    {
      if (cnt)
        mpn_lshift (my + sy - sx, mx, sx, cnt);
      else
        MPN_COPY (my + sy - sx, mx, sx);
      MPN_ZERO(my, sy - sx);
      /* no rounding necessary, since y has a larger mantissa */
      inexact = 0;
    }

  /* warning: EXP(x) * GMP_NUMB_BITS may exceed the maximal exponent */
  if (EXP(x) > 1 + (__gmpfr_emax - 1) / GMP_NUMB_BITS)
    {
      /* EXP(x) >= 2 + floor((__gmpfr_emax-1)/GMP_NUMB_BITS)
         EXP(x) >= 2 + (__gmpfr_emax - GMP_NUMB_BITS) / GMP_NUMB_BITS
                >= 1 + __gmpfr_emax / GMP_NUMB_BITS
         EXP(x) * GMP_NUMB_BITS >= __gmpfr_emax + GMP_NUMB_BITS
         Since 0 <= cnt <= GMP_NUMB_BITS-1, and 0 <= carry <= 1,
         we have then EXP(x) * GMP_NUMB_BITS - cnt + carry > __gmpfr_emax */
      return mpfr_overflow (y, rnd_mode, MPFR_SIGN (y));
    }
  else
    {
      /* Do not use MPFR_SET_EXP as the exponent may be out of range. */
      MPFR_EXP (y) = EXP (x) * GMP_NUMB_BITS - (mpfr_exp_t) cnt + carry;
    }

  return mpfr_check_range (y, inexact, rnd_mode);
}