static long double
ratio_to_long_double(cl_object num, cl_object den)
{
        cl_fixnum scale;
        cl_object bits = prepare_ratio_to_float(num, den, LDBL_MANT_DIG, &scale);
#if (FIXNUM_BITS-ECL_TAG_BITS) >= LDBL_MANT_DIG
        /* The output of prepare_ratio_to_float will always fit an integer */
        long double output = ecl_fixnum(bits);
#else
        long double output = ECL_FIXNUMP(bits)?
                (long double)ecl_fixnum(bits) :
                _ecl_big_to_long_double(bits);
#endif
        return ldexpl(output, scale);
}