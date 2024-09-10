// it moves vertically across blocks
void kernel_dsymv_4_lib4(int kmax, double *A, int sda, double *x_n, double *y_n, double *z_n, double *x_t, double *y_t, double *z_t, int tri, int alg)
	{
	
	if(kmax<=0) 
		return;

/*printf("\nciao %d\n", kmax);	*/
	const int bs = 4;
	
	__builtin_prefetch( A + bs*0 );
	__builtin_prefetch( A + bs*2 );

	int k, ka;
	ka = kmax; // number from aligned positon

	double k_left;
	
//	double *sA, *sy_n, *sx_t;

	static double d_mask[4]  = {0.5, 1.5, 2.5, 3.5};

	__m256d
		v_mask,
		zeros, temp,
		a_00, a_01, a_02, a_03,
		x_n_0, x_n_1, x_n_2, x_n_3, y_n_0,
		x_t_0, y_t_0, y_t_1, y_t_2, y_t_3;
	
	__m256i
		i_mask;

#if 0
	__m128d
		stemp,
		sa_00, sa_01, sa_02, sa_03,
		sx_n_0, sx_n_1, sx_n_2, sx_n_3, sy_n_0,
		sx_t_0, sy_t_0, sy_t_1, sy_t_2, sy_t_3;
#endif
	
	zeros = _mm256_setzero_pd();

	x_n_0 = _mm256_broadcast_sd( &x_n[0] );
	x_n_1 = _mm256_broadcast_sd( &x_n[1] );
	x_n_2 = _mm256_broadcast_sd( &x_n[2] );
	x_n_3 = _mm256_broadcast_sd( &x_n[3] );

	if(alg==-1) // TODO xor
		{
		x_n_0 = _mm256_sub_pd( zeros, x_n_0 );
		x_n_1 = _mm256_sub_pd( zeros, x_n_1 );
		x_n_2 = _mm256_sub_pd( zeros, x_n_2 );
		x_n_3 = _mm256_sub_pd( zeros, x_n_3 );
		}

	y_t_0 = _mm256_setzero_pd();
	y_t_1 = _mm256_setzero_pd();
	y_t_2 = _mm256_setzero_pd();
	y_t_3 = _mm256_setzero_pd();
	
#if 0
	sx_n_0 = _mm256_castpd256_pd128( x_n_0 );
	sx_n_1 = _mm256_castpd256_pd128( x_n_1 );
	sx_n_2 = _mm256_castpd256_pd128( x_n_2 );
	sx_n_3 = _mm256_castpd256_pd128( x_n_3 );

	sy_t_0 = _mm256_castpd256_pd128( y_t_0 );
	sy_t_1 = _mm256_castpd256_pd128( y_t_1 );
	sy_t_2 = _mm256_castpd256_pd128( y_t_2 );
	sy_t_3 = _mm256_castpd256_pd128( y_t_3 );

	k = bs*(ka/bs);
	sA = A + (ka/bs)*sda*bs;
	sy_n = y_n + (ka/bs)*bs;
	sx_t = x_t + (ka/bs)*bs;

	for(; k<ka; k++)
		{
		
		sy_n_0 = _mm_load_sd( &sy_n[0] );
		sx_t_0 = _mm_load_sd( &sx_t[0] );
		
		sa_00 = _mm_load_sd( &sA[0+bs*0] );
		sa_01 = _mm_load_sd( &sA[0+bs*1] );
		sa_02 = _mm_load_sd( &sA[0+bs*2] );
		sa_03 = _mm_load_sd( &sA[0+bs*3] );
		
		stemp  = _mm_mul_sd( sa_00, sx_n_0 );
		sy_n_0 = _mm_add_sd( sy_n_0, stemp );
		stemp  = _mm_mul_sd( sa_00, sx_t_0 );
		sy_t_0 = _mm_add_sd( sy_t_0, stemp );
		stemp  = _mm_mul_sd( sa_01, sx_n_1 );
		sy_n_0 = _mm_add_sd( sy_n_0, stemp );
		stemp  = _mm_mul_sd( sa_01, sx_t_0 );
		sy_t_1 = _mm_add_sd( sy_t_1, stemp );
		stemp  = _mm_mul_sd( sa_02, sx_n_2 );
		sy_n_0 = _mm_add_sd( sy_n_0, stemp );
		stemp  = _mm_mul_sd( sa_02, sx_t_0 );
		sy_t_2 = _mm_add_sd( sy_t_2, stemp );
		stemp  = _mm_mul_sd( sa_03, sx_n_3 );
		sy_n_0 = _mm_add_sd( sy_n_0, stemp );
		stemp  = _mm_mul_sd( sa_03, sx_t_0 );
		sy_t_3 = _mm_add_sd( sy_t_3, stemp );
		
		_mm_store_sd( &sy_n[0], sy_n_0 );

		
		sA += 1;
		sy_n += 1;
		sx_t += 1;

		}

	y_t_0 = _mm256_castpd128_pd256( sy_t_0 );
	y_t_1 = _mm256_castpd128_pd256( sy_t_1 );
	y_t_2 = _mm256_castpd128_pd256( sy_t_2 );
	y_t_3 = _mm256_castpd128_pd256( sy_t_3 );
#endif

	k=0;

	// corner
	if(tri==1)
		{
		
		__builtin_prefetch( A + sda*bs +bs*0 );
		__builtin_prefetch( A + sda*bs +bs*2 );

		y_n_0 = _mm256_loadu_pd( &y_n[0] );
		x_t_0 = _mm256_loadu_pd( &x_t[0] );
		
		a_00 = _mm256_load_pd( &A[0+bs*0] );
		a_01 = _mm256_load_pd( &A[0+bs*1] );
		a_02 = _mm256_load_pd( &A[0+bs*2] );
		a_03 = _mm256_load_pd( &A[0+bs*3] );
		
		temp  = _mm256_mul_pd( a_00, x_n_0 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_00, x_t_0 );
		temp  = _mm256_blend_pd( zeros, temp, 14 );
		y_t_0 = _mm256_add_pd( y_t_0, temp );
		temp  = _mm256_mul_pd( a_01, x_n_1 );
		temp  = _mm256_blend_pd( zeros, temp, 14 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_01, x_t_0 );
		temp  = _mm256_blend_pd( zeros, temp, 12 );
		y_t_1 = _mm256_add_pd( y_t_1, temp );
		temp  = _mm256_mul_pd( a_02, x_n_2 );
		temp  = _mm256_blend_pd( zeros, temp, 12 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_02, x_t_0 );
		temp  = _mm256_blend_pd( zeros, temp, 8 );
		y_t_2 = _mm256_add_pd( y_t_2, temp );
		temp  = _mm256_mul_pd( a_03, x_n_3 );
		temp  = _mm256_blend_pd( zeros, temp, 8 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		
		_mm256_storeu_pd( &z_n[0], y_n_0 );
		

		A += sda*bs;
		y_n += 4;
		z_n += 4;
		x_t += 4;

		k += 4;

		}

	for(; k<ka-7; k+=2*bs)
		{
		
		__builtin_prefetch( A + sda*bs +bs*0 );
		__builtin_prefetch( A + sda*bs +bs*2 );

		y_n_0 = _mm256_loadu_pd( &y_n[0] );
		x_t_0 = _mm256_loadu_pd( &x_t[0] );
		
		a_00 = _mm256_load_pd( &A[0+bs*0] );
		a_01 = _mm256_load_pd( &A[0+bs*1] );
		a_02 = _mm256_load_pd( &A[0+bs*2] );
		a_03 = _mm256_load_pd( &A[0+bs*3] );
		
		temp  = _mm256_mul_pd( a_00, x_n_0 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_00, x_t_0 );
		y_t_0 = _mm256_add_pd( y_t_0, temp );
		temp  = _mm256_mul_pd( a_01, x_n_1 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_01, x_t_0 );
		y_t_1 = _mm256_add_pd( y_t_1, temp );
		temp  = _mm256_mul_pd( a_02, x_n_2 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_02, x_t_0 );
		y_t_2 = _mm256_add_pd( y_t_2, temp );
		temp  = _mm256_mul_pd( a_03, x_n_3 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_03, x_t_0 );
		y_t_3 = _mm256_add_pd( y_t_3, temp );
		
		_mm256_storeu_pd( &z_n[0], y_n_0 );

		
		A += sda*bs;
		y_n += 4;
		z_n += 4;
		x_t += 4;

		__builtin_prefetch( A + sda*bs +bs*0 );
		__builtin_prefetch( A + sda*bs +bs*2 );

		y_n_0 = _mm256_loadu_pd( &y_n[0] );
		x_t_0 = _mm256_loadu_pd( &x_t[0] );
		
		a_00 = _mm256_load_pd( &A[0+bs*0] );
		a_01 = _mm256_load_pd( &A[0+bs*1] );
		a_02 = _mm256_load_pd( &A[0+bs*2] );
		a_03 = _mm256_load_pd( &A[0+bs*3] );
		
		temp  = _mm256_mul_pd( a_00, x_n_0 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_00, x_t_0 );
		y_t_0 = _mm256_add_pd( y_t_0, temp );
		temp  = _mm256_mul_pd( a_01, x_n_1 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_01, x_t_0 );
		y_t_1 = _mm256_add_pd( y_t_1, temp );
		temp  = _mm256_mul_pd( a_02, x_n_2 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_02, x_t_0 );
		y_t_2 = _mm256_add_pd( y_t_2, temp );
		temp  = _mm256_mul_pd( a_03, x_n_3 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_03, x_t_0 );
		y_t_3 = _mm256_add_pd( y_t_3, temp );
		
		_mm256_storeu_pd( &z_n[0], y_n_0 );

		
		A += sda*bs;
		y_n += 4;
		z_n += 4;
		x_t += 4;

		}

	for(; k<ka-3; k+=bs)
		{
		
		__builtin_prefetch( A + sda*bs +bs*0 );
		__builtin_prefetch( A + sda*bs +bs*2 );

		y_n_0 = _mm256_loadu_pd( &y_n[0] );
		x_t_0 = _mm256_loadu_pd( &x_t[0] );
		
		a_00 = _mm256_load_pd( &A[0+bs*0] );
		a_01 = _mm256_load_pd( &A[0+bs*1] );
		a_02 = _mm256_load_pd( &A[0+bs*2] );
		a_03 = _mm256_load_pd( &A[0+bs*3] );
		
		temp  = _mm256_mul_pd( a_00, x_n_0 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_00, x_t_0 );
		y_t_0 = _mm256_add_pd( y_t_0, temp );
		temp  = _mm256_mul_pd( a_01, x_n_1 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_01, x_t_0 );
		y_t_1 = _mm256_add_pd( y_t_1, temp );
		temp  = _mm256_mul_pd( a_02, x_n_2 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_02, x_t_0 );
		y_t_2 = _mm256_add_pd( y_t_2, temp );
		temp  = _mm256_mul_pd( a_03, x_n_3 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_03, x_t_0 );
		y_t_3 = _mm256_add_pd( y_t_3, temp );
		
		_mm256_storeu_pd( &z_n[0], y_n_0 );

		
		A += sda*bs;
		y_n += 4;
		z_n += 4;
		x_t += 4;

		}
	if(k<ka)
		{

		k_left = ka-k;
		v_mask  = _mm256_sub_pd( _mm256_loadu_pd( d_mask ), _mm256_broadcast_sd( &k_left ) );
		i_mask  = _mm256_castpd_si256( v_mask );

//		__builtin_prefetch( A + sda*bs +bs*0 );
//		__builtin_prefetch( A + sda*bs +bs*2 );

		y_n_0 = _mm256_loadu_pd( &y_n[0] );
		x_t_0 = _mm256_maskload_pd( &x_t[0], i_mask );
		
		a_00 = _mm256_load_pd( &A[0+bs*0] );
		a_01 = _mm256_load_pd( &A[0+bs*1] );
		a_02 = _mm256_load_pd( &A[0+bs*2] );
		a_03 = _mm256_load_pd( &A[0+bs*3] );
		
		temp  = _mm256_mul_pd( a_00, x_n_0 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_00, x_t_0 );
		y_t_0 = _mm256_add_pd( y_t_0, temp );
		temp  = _mm256_mul_pd( a_01, x_n_1 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_01, x_t_0 );
		y_t_1 = _mm256_add_pd( y_t_1, temp );
		temp  = _mm256_mul_pd( a_02, x_n_2 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_02, x_t_0 );
		y_t_2 = _mm256_add_pd( y_t_2, temp );
		temp  = _mm256_mul_pd( a_03, x_n_3 );
		y_n_0 = _mm256_add_pd( y_n_0, temp );
		temp  = _mm256_mul_pd( a_03, x_t_0 );
		y_t_3 = _mm256_add_pd( y_t_3, temp );
		
		_mm256_maskstore_pd( &z_n[0], i_mask, y_n_0 );

		
//		A += sda*bs;
//		y_n += 4;
//		z_n += 4;
//		x_t += 4;

		}
	
	__m256d
		y_0_1_2_3;

	y_t_0 = _mm256_hadd_pd( y_t_0, y_t_1 );
	y_t_2 = _mm256_hadd_pd( y_t_2, y_t_3 );

	y_t_1 = _mm256_permute2f128_pd( y_t_2, y_t_0, 2  );	
	y_t_0 = _mm256_permute2f128_pd( y_t_2, y_t_0, 19 );	

	y_t_0 = _mm256_add_pd( y_t_0, y_t_1 );

	if(alg==1)
		{
		y_0_1_2_3 = _mm256_loadu_pd( &y_t[0] );
		y_0_1_2_3 = _mm256_add_pd( y_0_1_2_3, y_t_0 );
		_mm256_storeu_pd( &z_t[0], y_0_1_2_3 );
		}
	else // alg==-1
		{
		y_0_1_2_3 = _mm256_loadu_pd( &y_t[0] );
		y_0_1_2_3 = _mm256_sub_pd( y_0_1_2_3, y_t_0 );
		_mm256_storeu_pd( &z_t[0], y_0_1_2_3 );
		}
	
	}