tuple solveCubicWrapper( double a, double b, double c, double d )
{
	double x[3];
	int s = solveCubic( a, b, c, d, x );
	switch( s )
	{
		case 0 :
			return tuple();
		case 1 :
			return make_tuple( x[0] );
		case 2 :
			return make_tuple( x[0], x[1] );
		case 3 :
			return make_tuple( x[0], x[1], x[2] );
		default :
			PyErr_SetString( PyExc_ArithmeticError, "Infinite solutions." );
			throw_error_already_set();
			return tuple(); // should never get here
	}
}