bool Cos(void)
{	bool ok = true;

	using CppAD::sin;
	using CppAD::cos;
	using namespace CppAD;

	// independent variable vector
	CPPAD_TESTVECTOR(AD<double>) U(1);
	U[0]     = 1.;
	Independent(U);

	// dependent variable vector 
	CPPAD_TESTVECTOR(AD<double>) Z(1);
	Z[0] = cos(U[0]); 

	// create f: U -> Z and vectors used for derivative calculations
	ADFun<double> f(U, Z); 
	CPPAD_TESTVECTOR(double) v(1);
	CPPAD_TESTVECTOR(double) w(1);

	// check value 
	double sin_u = sin( Value(U[0]) );
	double cos_u = cos( Value(U[0]) );

	ok &= NearEqual(cos_u, Value(Z[0]),  1e-10 , 1e-10);

	// forward computation of partials w.r.t. u
	size_t j;
	size_t p     = 5;
	double jfac  = 1.;
	v[0]         = 1.;
	for(j = 1; j < p; j++)
	{	w     = f.Forward(j, v);	

		double value;
		if( j % 4 == 1 )
			value = -sin_u;
		else if( j % 4 == 2 )
			value = -cos_u;
		else if( j % 4 == 3 )
			value = sin_u;
		else	value = cos_u;

		jfac *= j;
		ok &= NearEqual(jfac*w[0], value, 1e-10 , 1e-10); // d^jz/du^j
		v[0]  = 0.;
	}

	// reverse computation of partials of Taylor coefficients
	CPPAD_TESTVECTOR(double) r(p); 
	w[0]  = 1.;
	r     = f.Reverse(p, w);
	jfac  = 1.;
	for(j = 0; j < p; j++)
	{
		double value;
		if( j % 4 == 0 )
			value = -sin_u;
		else if( j % 4 == 1 )
			value = -cos_u;
		else if( j % 4 == 2 )
			value = sin_u;
		else	value = cos_u;

		ok &= NearEqual(jfac*r[j], value, 1e-10 , 1e-10); // d^jz/du^j

		jfac *= (j + 1);
	}

	return ok;
}