ScmObj Scm_MakeBignumFromDouble(double val)
{
    if (LONG_MIN <= val
#if SIZEOF_LONG == 4
        && val <= LONG_MAX
#else
        && val <= nextafter((double)LONG_MAX, 0.0)
#endif
        )
        return Scm_MakeBignumFromSI((long)val);

    int exponent, sign;
    ScmObj mantissa = Scm_DecodeFlonum(val, &exponent, &sign);
    if (!SCM_NUMBERP(mantissa)) {
        Scm_Error("can't convert %lf to an integer", val);
    }
    ScmObj b = Scm_Ash(mantissa, exponent);
    if (sign < 0) b = Scm_Negate(b);
    /* always returns bignum */
    if (SCM_INTP(b)) {
        return Scm_MakeBignumFromSI(SCM_INT_VALUE(b));
    } else {
        return b;
    }
}