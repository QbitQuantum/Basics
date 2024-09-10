long double
_ecl_big_to_long_double(cl_object o)
{
        long double output = 0;
        int i, l = mpz_size(o->big.big_num), exp = 0;
        for (i = 0; i < l; i++) {
                output += ldexpl(mpz_getlimbn(o->big.big_num, i), exp);
                exp += GMP_LIMB_BITS;
        }
        return (mpz_sgn(o->big.big_num) < 0)? -output : output;
}