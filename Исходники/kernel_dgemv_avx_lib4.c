void kernel_dgemv_t_4_lib4(int kmax, double *A, int sda, double *x, double *y, int alg)
	{

	if(kmax<=0) 
		return;
	
	const int lda = 4;
	
	__builtin_prefetch( A + 0*lda );
	__builtin_prefetch( A + 2*lda );

	double *tA, *tx;

	int k;
	int ka = kmax; // number from aligned positon
	
	__m256d
		aaxx_temp,
		a_00_10_20_30, a_01_11_21_31, a_02_12_22_32, a_03_13_23_33,
		x_0_1_2_3,
		y_00, y_11, y_22, y_33;
	
	__m128d
		ax_temp,
		a_00_10, a_01_11, a_02_12, a_03_13,
		x_0_1,
		y_0, y_1, y_2, y_3;
	
	y_00 = _mm256_setzero_pd();
	y_11 = _mm256_setzero_pd();
	y_22 = _mm256_setzero_pd();
	y_33 = _mm256_setzero_pd();
	
	y_0 = _mm256_castpd256_pd128(y_00);
	y_1 = _mm256_castpd256_pd128(y_11);
	y_2 = _mm256_castpd256_pd128(y_22);
	y_3 = _mm256_castpd256_pd128(y_33);

	k = lda*(ka/lda);
	tA = A + (ka/lda)*sda*lda;
	tx = x + (ka/lda)*lda;

	for(; k<ka; k++)
		{
		x_0_1 = _mm_load_sd( &tx[0] );

		a_00_10 = _mm_load_sd( &tA[0+lda*0] );
		a_01_11 = _mm_load_sd( &tA[0+lda*1] );
		a_02_12 = _mm_load_sd( &tA[0+lda*2] );
		a_03_13 = _mm_load_sd( &tA[0+lda*3] );
		
			ax_temp = _mm_mul_sd( a_00_10, x_0_1 );	
			y_0 = _mm_add_sd (y_0, ax_temp );
			ax_temp = _mm_mul_sd( a_01_11, x_0_1 );	
			y_1 = _mm_add_sd (y_1, ax_temp );
			ax_temp = _mm_mul_sd( a_02_12, x_0_1 );	
			y_2 = _mm_add_sd (y_2, ax_temp );
			ax_temp = _mm_mul_sd( a_03_13, x_0_1 );	
			y_3 = _mm_add_sd (y_3, ax_temp );
		
		tA += 1;
		tx += 1;

		}

	y_00 = _mm256_castpd128_pd256(y_0);
	y_11 = _mm256_castpd128_pd256(y_1);
	y_22 = _mm256_castpd128_pd256(y_2);
	y_33 = _mm256_castpd128_pd256(y_3);

	k=0;
	for(; k<ka-7; k+=8)
		{
		
		__builtin_prefetch( A + sda*lda + 0*lda );
		__builtin_prefetch( A + sda*lda + 2*lda );

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );
		a_02_12_22_32 = _mm256_load_pd( &A[0+lda*2] );
		a_03_13_23_33 = _mm256_load_pd( &A[0+lda*3] );
		
		aaxx_temp = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, aaxx_temp );
		aaxx_temp = _mm256_mul_pd( a_01_11_21_31, x_0_1_2_3 );
		y_11 = _mm256_add_pd( y_11, aaxx_temp );
		aaxx_temp = _mm256_mul_pd( a_02_12_22_32, x_0_1_2_3 );
		y_22 = _mm256_add_pd( y_22, aaxx_temp );
		aaxx_temp = _mm256_mul_pd( a_03_13_23_33, x_0_1_2_3 );
		y_33 = _mm256_add_pd( y_33, aaxx_temp );
		
		A += 4 + (sda-1)*lda;
		x += 4;


		__builtin_prefetch( A + sda*lda + 0*lda );
		__builtin_prefetch( A + sda*lda + 2*lda );

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );
		a_02_12_22_32 = _mm256_load_pd( &A[0+lda*2] );
		a_03_13_23_33 = _mm256_load_pd( &A[0+lda*3] );
		
		aaxx_temp = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, aaxx_temp );
		aaxx_temp = _mm256_mul_pd( a_01_11_21_31, x_0_1_2_3 );
		y_11 = _mm256_add_pd( y_11, aaxx_temp );
		aaxx_temp = _mm256_mul_pd( a_02_12_22_32, x_0_1_2_3 );
		y_22 = _mm256_add_pd( y_22, aaxx_temp );
		aaxx_temp = _mm256_mul_pd( a_03_13_23_33, x_0_1_2_3 );
		y_33 = _mm256_add_pd( y_33, aaxx_temp );
		
		A += 4 + (sda-1)*lda;
		x += 4;

		}
	for(; k<ka-3; k+=4)
		{
		
		__builtin_prefetch( A + sda*lda + 0*lda );
		__builtin_prefetch( A + sda*lda + 2*lda );

		x_0_1_2_3 = _mm256_loadu_pd( &x[0] );

		a_00_10_20_30 = _mm256_load_pd( &A[0+lda*0] );
		a_01_11_21_31 = _mm256_load_pd( &A[0+lda*1] );
		a_02_12_22_32 = _mm256_load_pd( &A[0+lda*2] );
		a_03_13_23_33 = _mm256_load_pd( &A[0+lda*3] );
		
		aaxx_temp = _mm256_mul_pd( a_00_10_20_30, x_0_1_2_3 );
		y_00 = _mm256_add_pd( y_00, aaxx_temp );
		aaxx_temp = _mm256_mul_pd( a_01_11_21_31, x_0_1_2_3 );
		y_11 = _mm256_add_pd( y_11, aaxx_temp );
		aaxx_temp = _mm256_mul_pd( a_02_12_22_32, x_0_1_2_3 );
		y_22 = _mm256_add_pd( y_22, aaxx_temp );
		aaxx_temp = _mm256_mul_pd( a_03_13_23_33, x_0_1_2_3 );
		y_33 = _mm256_add_pd( y_33, aaxx_temp );
		
		A += 4 + (sda-1)*lda;
		x += 4;

		}

	__m256d
		y_0_1_2_3;

	y_00 = _mm256_hadd_pd(y_00, y_11);
	y_22 = _mm256_hadd_pd(y_22, y_33);

	y_11 = _mm256_permute2f128_pd(y_22, y_00, 2 );	
	y_00 = _mm256_permute2f128_pd(y_22, y_00, 19);	

	y_00 = _mm256_add_pd( y_00, y_11 );

	if(alg==0)
		{
		_mm256_storeu_pd(&y[0], y_00);
		}
	else if(alg==1)
		{
		y_0_1_2_3 = _mm256_loadu_pd( &y[0] );

		y_0_1_2_3 = _mm256_add_pd( y_0_1_2_3, y_00 );

		_mm256_storeu_pd(&y[0], y_0_1_2_3);
		}
	else // alg==-1
		{
		y_0_1_2_3 = _mm256_loadu_pd( &y[0] );
	
		y_0_1_2_3 = _mm256_sub_pd( y_0_1_2_3, y_00 );
	
		_mm256_storeu_pd(&y[0], y_0_1_2_3);
		}

	}