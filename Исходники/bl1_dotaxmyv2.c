void bl1_ddotaxmyv2( int       n,
                     double*   alpha,
                     double*   beta,
                     double*   x, int inc_x,
                     double*   u, int inc_u,
                     double*   rho,
                     double*   y, int inc_y,
                     double*   z, int inc_z )
#if BLIS1_VECTOR_INTRINSIC_TYPE == BLIS1_SSE_INTRINSICS
{
	double*   restrict chi1;
	double*   restrict upsilon1;
	double*   restrict psi1;
	double*   restrict zeta1;
	double    rho_c;
	int       i;

	int       n_pre;
	int       n_run;
	int       n_left;

	v2df_t    a1v, b1v;
	v2df_t    rho1v;
	v2df_t    x1v, u1v, y1v, z1v;

	if ( inc_x != 1 ||
	     inc_u != 1 ||
	     inc_y != 1 ||
	     inc_z != 1 ) bl1_abort();

	n_pre = 0;
	if ( ( unsigned long ) z % 16 != 0 )
	{
		if ( ( unsigned long ) x % 16 == 0 ||
		     ( unsigned long ) u % 16 == 0 ||
		     ( unsigned long ) y % 16 == 0 ) bl1_abort();

		n_pre = 1;
	}

	n_run       = ( n - n_pre ) / 2;
	n_left      = ( n - n_pre ) % 2;

	chi1     = x;
	upsilon1 = u;
	psi1     = y;
	zeta1    = z;

	rho_c   = 0.0;

	if ( n_pre == 1 )
	{
		double   alpha_c = *alpha;
		double   beta_c  = *beta;
		double   chi1_c    = *chi1;
		double   upsilon_c = *upsilon1;

		rho_c  += chi1_c * upsilon_c;
		*psi1  -= alpha_c * chi1_c;
		*zeta1 -= beta_c  * chi1_c;

		chi1     += inc_x;
		upsilon1 += inc_u;
		psi1     += inc_y;
		zeta1    += inc_z;
	}

	a1v.v = _mm_loaddup_pd( ( double* )alpha );
	b1v.v = _mm_loaddup_pd( ( double* )beta );

	rho1v.v = _mm_setzero_pd();

	for ( i = 0; i < n_run; ++i )
	{
		x1v.v = _mm_load_pd( ( double* )chi1 );
		u1v.v = _mm_load_pd( ( double* )upsilon1 );
		y1v.v = _mm_load_pd( ( double* )psi1 );
		z1v.v = _mm_load_pd( ( double* )zeta1 );

		rho1v.v += x1v.v * u1v.v;
		y1v.v   -= a1v.v * x1v.v;
		z1v.v   -= b1v.v * x1v.v;

		_mm_store_pd( ( double* )psi1,  y1v.v );
		_mm_store_pd( ( double* )zeta1, z1v.v );

		chi1     += 2;
		upsilon1 += 2;
		psi1     += 2;
		zeta1    += 2;
	}

	rho_c += rho1v.d[0] + rho1v.d[1];

	if ( n_left > 0 )
	{
		double   alpha_c = *alpha;
		double   beta_c  = *beta;

		for( i = 0; i < n_left; ++i )
		{
			double   chi1_c    = *chi1;
			double   upsilon_c = *upsilon1;

			rho_c  += chi1_c * upsilon_c;
			*psi1  -= alpha_c * chi1_c;
			*zeta1 -= beta_c  * chi1_c;

			chi1     += inc_x;
			upsilon1 += inc_u;
			psi1     += inc_y;
			zeta1    += inc_z;
		}
	}

	*rho = rho_c;
}