static CSLbool numeqsr(Lisp_Object a, Lisp_Object b)
/*
 * Here I will rely somewhat on the use of IEEE floating point values
 * (an in particular the weaker supposition that I have floating point
 * with a binary radix).  Then for equality the denominator of b must
 * be a power of 2, which I can test for and then account for.
 */
{
    Lisp_Object nb = numerator(b), db = denominator(b);
    double d = float_of_number(a), d1;
    int x;
    int32_t dx, w, len;
    uint32_t u, bit;
    /*
     * first I will check that db (which will be positive) is a power of 2,
     * and set dx to indicate what power of two it is.
     * Note that db != 0 and that one of the top two words of a bignum
     * must be nonzero (for normalisation) so I end up with a nonzero
     * value in the variable 'bit'
     */
    if (is_fixnum(db))
    {   bit = int_of_fixnum(db);
        w = bit;
        if (w != (w & (-w))) return NO;   /* not a power of 2 */
        dx = 0;
    }
    else if (is_numbers(db) && is_bignum(db))
    {   int32_t lenb = (bignum_length(db)-CELL-4)/4;
        bit = bignum_digits(db)[lenb];
        /*
         * I need to cope with bignums where the leading digits is zero because
         * the 0x80000000 bit of the next word down is 1.  To do this I treat
         * the number as having one fewer digits.
         */
        if (bit == 0) bit = bignum_digits(db)[--lenb];
        w = bit;
        if (w != (w & (-w))) return NO;   /* not a power of 2 */
        dx = 31*lenb;
        while (--lenb >= 0)     /* check that the rest of db is zero */
            if (bignum_digits(db)[lenb] != 0) return NO;
    }
    else return NO; /* Odd - what type IS db here?  Maybe error. */
    if ((bit & 0xffffU) == 0) dx += 16, bit = bit >> 16;
    if ((bit & 0xff) == 0) dx += 8, bit = bit >> 8;
    if ((bit & 0xf) == 0) dx += 4, bit = bit >> 4;
    if ((bit & 0x3) == 0) dx += 2, bit = bit >> 2;
    if ((bit & 0x1) == 0) dx += 1;
    if (is_fixnum(nb))
    {   double d1 = (double)int_of_fixnum(nb);
        /*
         * The ldexp on the next line could potentially underflow.  In that case C
         * defines that the result 0.0 be returned.  To avoid trouble I put in a
         * special test the relies on that fact that a value represented as a rational
         * would not have been zero.
         */
        if (dx > 10000) return NO;  /* Avoid gross underflow */
        d1 = ldexp(d1, (int)-dx);
        return (d == d1 && d != 0.0);
    }
    len = (bignum_length(nb)-CELL-4)/4;
    if (len == 0)   /* One word bignums can be treated specially */
    {   int32_t v = bignum_digits(nb)[0];
        double d1;
        if (dx > 10000) return NO;  /* Avoid gross underflow */
        d1 = ldexp((double)v, (int)-dx);
        return (d == d1 && d != 0.0);
    }
    d1 = frexp(d, &x);    /* separate exponent from mantissa */
    if (d1 == 1.0) d1 = 0.5, x++; /* For Zortech */
    dx += x;              /* adjust to allow for the denominator */
    d1 = ldexp(d1, (int)(dx % 31));
    /* can neither underflow nor overflow here */
    /*
     * At most 3 words in the bignum may contain nonzero data - I subtract
     * the (double) value of those bits off and check that (a) the floating
     * result left is zero and (b) there are no more bits left.
     */
    dx = dx / 31;
    if (dx != len) return NO;
    w = bignum_digits(nb)[len];
    d1 = (d1 - (double)w) * TWO_31;
    u = bignum_digits(nb)[--len];
    d1 = (d1 - (double)u) * TWO_31;
    if (len > 0)
    {   u = bignum_digits(nb)[--len];
        d1 = d1 - (double)u;
    }
    if (d1 != 0.0) return NO;
    while (--len >= 0)
        if (bignum_digits(nb)[len] != 0) return NO;
    return YES;
}