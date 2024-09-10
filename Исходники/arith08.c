static Lisp_Object lisp_fix_sub(Lisp_Object a, int roundmode)
/*
 * This converts from a double to a Lisp integer, which will
 * quite often have to be a bignum.  No overflow is permitted - the
 * result can always be accurate.
 */
{
    int32_t a0, a1, a2, a3;
    int x, x1;
    CSLbool negative;
    double d = float_of_number(a);
    if (M2_31_1 < d && d < TWO_31)
    {   int32_t a = (int32_t)d;
/*
 * If my floating point value is in the range -(2^31+1) to +2^31 (exclusive)
 * then when C truncates it I will get an integer in the inclusive range
 * from -2^31 to 2^31-1, i.e. the whole range of C 32-bit integers.
 * If I then apply a rounding mode other than truncation I may just have
 * overflow, which I have to detect specially.
 */
        int32_t w;
        double f;
        switch (roundmode)
        {
    case FIX_TRUNCATE:
            break;          /* C casts truncate, so this is OK */
    case FIX_ROUND:
            f = d - (double)a;
            if (f > 0.5)
            {   if (a == 0x7fffffff) return make_two_word_bignum(1, 0);
                else a++;
            }
            else if (f < -0.5)
            {   if (a == ~0x7fffffff)
                    return make_two_word_bignum(-2, 0x7fffffff);
                else a--;
            }
   /* The rounding rule on the next lines show what I do in 1/2ulp cases */
            else if (f == 0.5) a = (a+1) & ~1;
            else if (f == -0.5)
            {   if (a == ~0x7fffffff)
                    return make_two_word_bignum(-2, 0x7fffffff);
                else a = a & ~1;
            }
            break;
    case FIX_FLOOR:
            f = d - (double)a;
            if (f < 0.0)
            {   if (a == ~0x7fffffff)
                    return make_two_word_bignum(-2, 0x7fffffff);
                else a--;
            }
            break;
    case FIX_CEILING:
            f = d - (double)a;
            if (f > 0.0)
            {   if (a == 0x7fffffff) return make_two_word_bignum(1, 0);
                else a++;
            }
            break;
        }
        w = a & fix_mask;
        if (w == 0 || w == fix_mask) return fixnum_of_int(a);
        else if (!signed_overflow(a)) return make_one_word_bignum(a);
        else if (a > 0) return make_two_word_bignum(0, a);
        else return make_two_word_bignum(-1, clear_top_bit(a));
    }
    if (d < 0.0) d = -d, negative = YES;
    else negative = NO;
    d = frexp(d, &x); /* 0.5 <= abs(d) < 1.0, x = the (binary) exponent */
    if (d == 1.0) d = 0.5, x++;
    d *= TWO_31;
    a1 = (int32_t)d;      /* 2^31 > d >= 2^30 */
    d -= (double)a1;
    a2 = (uint32_t)(d*TWO_31);  /* This conversion should be exact */
    if (negative)
    {   if (a2 == 0) a1 = -a1;
        else a2 = clear_top_bit(-a2), a1 = ~a1;
    }
    x -= 62;
    if (x < 0)              /* Need to shift right x places */
    {   x = -x;             /* The shift amount here can be 31 at most... */
        a3 = a2 << (32 - x);
        a2 = clear_top_bit((a2 >> x) | (a1 << (31 - x)));
#ifdef SIGNED_SHIFTS_ARE_LOGICAL
        if (a1 < 0) a1 = (a1 >> x) | (((int32_t)-1) << (31 - x));
        else a1 = a1 >> x;