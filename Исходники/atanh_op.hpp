inline void forward_atanh_op_0(
	size_t i_z         ,
	size_t i_x         ,
	size_t cap_order   ,
	Base*  taylor      )
{
	// check assumptions
	CPPAD_ASSERT_UNKNOWN( NumArg(AtanhOp) == 1 );
	CPPAD_ASSERT_UNKNOWN( NumRes(AtanhOp) == 2 );
	CPPAD_ASSERT_UNKNOWN( 0 < cap_order );

	// Taylor coefficients corresponding to argument and result
	Base* x = taylor + i_x * cap_order;
	Base* z = taylor + i_z * cap_order;
	Base* b = z      -       cap_order; // called y in documentation

	z[0] = atanh( x[0] );
	b[0] = Base(1) - x[0] * x[0];
}