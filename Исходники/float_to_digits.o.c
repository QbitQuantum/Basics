static float_approx *
setup(cl_object number, float_approx *approx)
{
        cl_object f = cl_integer_decode_float(number);
        cl_fixnum e = ecl_fixnum(VALUES(1)), min_e;
        bool limit_f = 0;
        switch (ecl_t_of(number)) {
        case t_singlefloat:
                min_e = FLT_MIN_EXP;
                limit_f = (number->SF.SFVAL ==
                           ldexpf(FLT_RADIX, FLT_MANT_DIG-1));
                break;
        case t_doublefloat:
                min_e = DBL_MIN_EXP;
                limit_f = (number->DF.DFVAL ==
                           ldexp(FLT_RADIX, DBL_MANT_DIG-1));
                break;
#ifdef ECL_LONG_FLOAT
        case t_longfloat:
                min_e = LDBL_MIN_EXP;
                limit_f = (number->longfloat.value ==
                           ldexpl(FLT_RADIX, LDBL_MANT_DIG-1));
#endif
        }
        approx->low_ok = approx->high_ok = ecl_evenp(f);
        if (e > 0) {
                cl_object be = EXPT_RADIX(e);
                if (limit_f) {
                        cl_object be1 = ecl_times(be, ecl_make_fixnum(FLT_RADIX));
                        approx->r = times2(ecl_times(f, be1));
                        approx->s = ecl_make_fixnum(FLT_RADIX*2);
                        approx->mm = be;
                        approx->mp = be1;
                } else {
                        approx->r = times2(ecl_times(f, be));
                        approx->s = ecl_make_fixnum(2);
                        approx->mm = be;
                        approx->mp = be;
                }
        } else if (!limit_f || (e == min_e)) {
                approx->r = times2(f);
                approx->s = times2(EXPT_RADIX(-e));
                approx->mp = ecl_make_fixnum(1);
                approx->mm = ecl_make_fixnum(1);
        } else {
                approx->r = times2(ecl_make_fixnum(FLT_RADIX));
                approx->s = times2(EXPT_RADIX(1-e));
                approx->mp = ecl_make_fixnum(FLT_RADIX);
                approx->mm = ecl_make_fixnum(1);
        }
        return approx;
}