void kernel_strmv_u_t_4_lib8(int kmax, float *A, int sda, float *x, float *y, int alg)
	{

/*	if(kmax<=0) */
/*		return;*/
	
	const int lda = 8;
/*	const int bs  = 8;*/
	
	__builtin_prefetch( A + 0*lda );
	__builtin_prefetch( A + 2*lda );

	int
		k;
	
	__m256
		zeros,
		ax_temp,
		a_00, a_01, a_02, a_03,
		x_0,
		y_0, y_1, y_2, y_3, y_4, y_5, y_6, y_7;
	
	zeros = _mm256_setzero_ps();

	y_0 = _mm256_setzero_ps();
	y_1 = _mm256_setzero_ps();
	y_2 = _mm256_setzero_ps();
	y_3 = _mm256_setzero_ps();
	y_4 = _mm256_setzero_ps();
	y_5 = _mm256_setzero_ps();
	y_6 = _mm256_setzero_ps();
	y_7 = _mm256_setzero_ps();
	
	k=0;
	for(; k<kmax-7; k+=8)
		{
		
		x_0 = _mm256_loadu_ps( &x[0] );

		__builtin_prefetch( A + sda*lda + 0*lda );
		__builtin_prefetch( A + sda*lda + 2*lda );

		a_00 = _mm256_load_ps( &A[0+lda*0] );
		ax_temp = _mm256_mul_ps( a_00, x_0 );
		y_0 = _mm256_add_ps( y_0, ax_temp );
		a_01 = _mm256_load_ps( &A[0+lda*1] );
		ax_temp = _mm256_mul_ps( a_01, x_0 );
		y_1 = _mm256_add_ps( y_1, ax_temp );
		a_02 = _mm256_load_ps( &A[0+lda*2] );
		ax_temp = _mm256_mul_ps( a_02, x_0 );
		y_2 = _mm256_add_ps( y_2, ax_temp );
		a_03 = _mm256_load_ps( &A[0+lda*3] );
		ax_temp = _mm256_mul_ps( a_03, x_0 );
		y_3 = _mm256_add_ps( y_3, ax_temp );
		
		A += sda*lda;
		x += 8;

		}

	x_0 = _mm256_loadu_ps( &x[0] );

	a_00 = _mm256_load_ps( &A[0+lda*0] );
	a_00 = _mm256_blend_ps( zeros, a_00, 0x01 );
	ax_temp = _mm256_mul_ps( a_00, x_0 );
	y_0 = _mm256_add_ps( y_0, ax_temp );
	a_01 = _mm256_load_ps( &A[0+lda*1] );
	a_01 = _mm256_blend_ps( zeros, a_01, 0x03 );
	ax_temp = _mm256_mul_ps( a_01, x_0 );
	y_1 = _mm256_add_ps( y_1, ax_temp );
	a_02 = _mm256_load_ps( &A[0+lda*2] );
	a_02 = _mm256_blend_ps( zeros, a_02, 0x07 );
	ax_temp = _mm256_mul_ps( a_02, x_0 );
	y_2 = _mm256_add_ps( y_2, ax_temp );
	a_03 = _mm256_load_ps( &A[0+lda*3] );
	a_03 = _mm256_blend_ps( zeros, a_03, 0x0f );
	ax_temp = _mm256_mul_ps( a_03, x_0 );
	y_3 = _mm256_add_ps( y_3, ax_temp );

	// reduction
	__m128
		z_0, z_1;

	y_0 = _mm256_hadd_ps(y_0, y_1);
	y_2 = _mm256_hadd_ps(y_2, y_3);

	y_0 = _mm256_hadd_ps(y_0, y_2);

	y_1 = _mm256_permute2f128_ps(y_0, y_0, 0x01);
	
	z_0 = _mm256_castps256_ps128(y_0);
	z_1 = _mm256_castps256_ps128(y_1);
	
	z_1 = _mm_add_ps(z_0, z_1);

	if(alg==0)
		{
		_mm_storeu_ps(&y[0], z_1);
		}
	else if(alg==1)
		{
		z_0 = _mm_loadu_ps( &y[0] );

		z_0 = _mm_add_ps(z_0, z_1);

		_mm_storeu_ps(&y[0], z_0);
		}
	else // alg==-1
		{
		z_0 = _mm_loadu_ps( &y[0] );

		z_0 = _mm_sub_ps(z_0, z_1);

		_mm_storeu_ps(&y[0], z_0);
		}

	}