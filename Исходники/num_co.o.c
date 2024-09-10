cl_object
cl_scale_float(cl_object x, cl_object y)
{
	const cl_env_ptr the_env = ecl_process_env();
	cl_fixnum k;

	if (ECL_FIXNUMP(y)) {
		k = ecl_fixnum(y);
	} else {
		FEwrong_type_nth_arg(ecl_make_fixnum(/*SCALE-FLOAT*/737),2,y,ecl_make_fixnum(/*FIXNUM*/372));
	}
	switch (ecl_t_of(x)) {
	case t_singlefloat:
		x = ecl_make_single_float(ldexpf(ecl_single_float(x), k));
		break;
	case t_doublefloat:
		x = ecl_make_double_float(ldexp(ecl_double_float(x), k));
		break;
#ifdef ECL_LONG_FLOAT
	case t_longfloat:
		x = ecl_make_long_float(ldexpl(ecl_long_float(x), k));
		break;
#endif
	default:
                FEwrong_type_nth_arg(ecl_make_fixnum(/*SCALE-FLOAT*/737),1,x,ecl_make_fixnum(/*FLOAT*/374));
	}
	ecl_return1(the_env, x);
}