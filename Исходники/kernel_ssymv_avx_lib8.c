void kernel_ssymv_4_lib8(int kmax, int kna, float *A, int sda, float *x_n, float *y_n, float *x_t, float *y_t, int tri, int alg)
	{
	
	if(kmax<=0) 
		return;
	
	const int lda = 8;
	
	__builtin_prefetch( A + 0*lda );
	__builtin_prefetch( A + 2*lda );

	int 
		k, k_left, ii;
	
	float 
		k_left_d;

	const float mask_f[] = {7.5, 6.5, 5.5, 4.5, 3.5, 2.5, 1.5, 0.5};
	float temp_space[8] = {};

	__m256
		mask,
		zeros, temp,
		a_00, a_01, a_02, a_03,
		x_n_0, x_n_1, x_n_2, x_n_3, y_n_0,
		x_t_0, y_t_0, y_t_1, y_t_2, y_t_3;
	
	mask = _mm256_loadu_ps( mask_f ); 

	zeros = _mm256_setzero_ps();

	x_n_0 = _mm256_broadcast_ss( &x_n[0] );
	x_n_1 = _mm256_broadcast_ss( &x_n[1] );
	x_n_2 = _mm256_broadcast_ss( &x_n[2] );
	x_n_3 = _mm256_broadcast_ss( &x_n[3] );

	if(alg==-1) // TODO xor
		{
		x_n_0 = _mm256_sub_ps( zeros, x_n_0 );
		x_n_1 = _mm256_sub_ps( zeros, x_n_1 );
		x_n_2 = _mm256_sub_ps( zeros, x_n_2 );
		x_n_3 = _mm256_sub_ps( zeros, x_n_3 );
		}

	y_t_0 = _mm256_setzero_ps();
	y_t_1 = _mm256_setzero_ps();
	y_t_2 = _mm256_setzero_ps();
	y_t_3 = _mm256_setzero_ps();
	
	k=0;

	// corner
	if(tri==1)
		{
		
		k_left = kna-k;

		k_left_d = 8.0 - k_left;
/*printf("\nk_left = %d\n", k_left);*/

/*		y_n_0 = _mm_load_ps( &y_n[0] );*/
/*		y_n_0 = _mm_setzero_ps();*/
		x_t_0 = _mm256_loadu_ps( &x_t[0] );
		x_t_0 = _mm256_blendv_ps( x_t_0, zeros, _mm256_sub_ps( mask, _mm256_broadcast_ss( &k_left_d) ) );

/*_mm256_storeu_ps( temp_space, x_t_0 );		*/
/*printf("\nx = %f %f %f %f %f %f %f %f \n", temp_space[0], temp_space[1], temp_space[2], temp_space[3], temp_space[4], temp_space[5], temp_space[6], temp_space[7] );*/
/*exit(1);*/

		a_00  = _mm256_loadu_ps( &A[0+lda*0] );
		a_00  = _mm256_blend_ps( a_00, zeros, 0x00 );
/*		temp  = _mm256_mul_ps( a_00, x_n_0 );*/
/*		y_n_0 = _mm256_add_ps( y_n_0, temp );*/
		y_n_0 = _mm256_mul_ps( a_00, x_n_0 );
		a_00  = _mm256_blend_ps( a_00, zeros, 0x01 );
		temp  = _mm256_mul_ps( a_00, x_t_0 );
		y_t_0 = _mm256_add_ps( y_t_0, temp );

		a_01  = _mm256_loadu_ps( &A[0+lda*1] );
		a_01  = _mm256_blend_ps( a_01, zeros, 0x01 );
		temp  = _mm256_mul_ps( a_01, x_n_1 );
		y_n_0 = _mm256_add_ps( y_n_0, temp );
		a_01  = _mm256_blend_ps( a_01, zeros, 0x03 );
		temp  = _mm256_mul_ps( a_01, x_t_0 );
		y_t_1 = _mm256_add_ps( y_t_1, temp );

		a_02  = _mm256_loadu_ps( &A[0+lda*2] );
		a_02  = _mm256_blend_ps( a_02, zeros, 0x03 );
		temp  = _mm256_mul_ps( a_02, x_n_2 );
		y_n_0 = _mm256_add_ps( y_n_0, temp );
		a_02  = _mm256_blend_ps( a_02, zeros, 0x07 );
		temp  = _mm256_mul_ps( a_02, x_t_0 );
		y_t_2 = _mm256_add_ps( y_t_2, temp );

		a_03  = _mm256_loadu_ps( &A[0+lda*3] );
		a_03  = _mm256_blend_ps( a_03, zeros, 0x07 );
		temp  = _mm256_mul_ps( a_03, x_n_3 );
		y_n_0 = _mm256_add_ps( y_n_0, temp );
		a_03  = _mm256_blend_ps( a_03, zeros, 0x0f );
		temp  = _mm256_mul_ps( a_03, x_t_0 );
		y_t_3 = _mm256_add_ps( y_t_3, temp );
		
/*_mm256_storeu_ps( temp_space, y_n_0 );		*/
/*printf("\ny = %f %f %f %f %f %f %f %f \n", temp_space[0], temp_space[1], temp_space[2], temp_space[3], temp_space[4], temp_space[5], temp_space[6], temp_space[7] );*/
		y_n_0 = _mm256_blendv_ps( y_n_0, zeros, _mm256_sub_ps( mask, _mm256_broadcast_ss( &k_left_d) ) );
/*_mm256_storeu_ps( temp_space, y_n_0 );		*/
/*printf("\ny = %f %f %f %f %f %f %f %f \n", temp_space[0], temp_space[1], temp_space[2], temp_space[3], temp_space[4], temp_space[5], temp_space[6], temp_space[7] );*/
		x_t_0 = _mm256_loadu_ps( &y_n[0] );
		y_n_0 = _mm256_add_ps( y_n_0, x_t_0 );
		_mm256_storeu_ps( &y_n[0], y_n_0 );
		

		A   += k_left;
		y_n += k_left;
		x_t += k_left;

		k   += k_left;

		}

	if(k<kna) // it can be only k_left = {1, 2, 3, 4, 5, 6, 7}
/*	for(; k<kna; k++)*/
		{
		
		k_left = kna-k;

		k_left_d = 8.0 - k_left;
/*printf("\nk_left = %d\n", k_left);*/

/*		y_n_0 = _mm_load_ps( &y_n[0] );*/
/*		y_n_0 = _mm_setzero_ps();*/
		x_t_0 = _mm256_loadu_ps( &x_t[0] );
		x_t_0 = _mm256_blendv_ps( x_t_0, zeros, _mm256_sub_ps( mask, _mm256_broadcast_ss( &k_left_d) ) );
/*_mm256_storeu_ps( temp_space, x_t_0 );		*/
/*printf("\nx = %f %f %f %f %f %f %f %f \n", temp_space[0], temp_space[1], temp_space[2], temp_space[3], temp_space[4], temp_space[5], temp_space[6], temp_space[7] );*/
		
		a_00  = _mm256_loadu_ps( &A[0+lda*0] );
		a_01  = _mm256_loadu_ps( &A[0+lda*1] );
		a_02  = _mm256_loadu_ps( &A[0+lda*2] );
		a_03  = _mm256_loadu_ps( &A[0+lda*3] );
		
/*		temp  = _mm256_mul_ps( a_00, x_n_0 );*/
/*		y_n_0 = _mm256_add_ps( y_n_0, temp );*/
		y_n_0 = _mm256_mul_ps( a_00, x_n_0 );
		temp  = _mm256_mul_ps( a_00, x_t_0 );
		y_t_0 = _mm256_add_ps( y_t_0, temp );
		temp  = _mm256_mul_ps( a_01, x_n_1 );
		y_n_0 = _mm256_add_ps( y_n_0, temp );
		temp  = _mm256_mul_ps( a_01, x_t_0 );
		y_t_1 = _mm256_add_ps( y_t_1, temp );
		temp  = _mm256_mul_ps( a_02, x_n_2 );
		y_n_0 = _mm256_add_ps( y_n_0, temp );
		temp  = _mm256_mul_ps( a_02, x_t_0 );
		y_t_2 = _mm256_add_ps( y_t_2, temp );
		temp  = _mm256_mul_ps( a_03, x_n_3 );
		y_n_0 = _mm256_add_ps( y_n_0, temp );
		temp  = _mm256_mul_ps( a_03, x_t_0 );
		y_t_3 = _mm256_add_ps( y_t_3, temp );
		
		y_n_0 = _mm256_blendv_ps( y_n_0, zeros, _mm256_sub_ps( mask, _mm256_broadcast_ss( &k_left_d) ) );
		x_t_0 = _mm256_loadu_ps( &y_n[0] );
		y_n_0 = _mm256_add_ps( y_n_0, x_t_0 );
		_mm256_storeu_ps( &y_n[0], y_n_0 );
/*		_mm256_maskstore_ps( &y_n[0], (__m256i) _mm256_sub_ps( mask, _mm256_broadcast_ss( &k_left_d) ), y_n_0 );*/

/*		_mm256_storeu_ps( temp_space, y_n_0 );*/
/*		for(ii=0; ii<k_left; ii++)*/
/*			y_n[ii] = temp_space[ii];*/

/*printf("\nk_left = %d\n", k_left);*/
/*exit(1);*/
	
		A   += k_left;
		y_n += k_left;
		x_t += k_left;

		k   += k_left;
		
		}
	if(kna>0 || tri==1)
		{
		A += (sda-1)*lda;
		}
	for(; k<kmax-7; k+=8)
		{
		
		__builtin_prefetch( A + sda*lda + 0*lda );
		__builtin_prefetch( A + sda*lda + 2*lda );

		y_n_0 = _mm256_loadu_ps( &y_n[0] );
		x_t_0 = _mm256_loadu_ps( &x_t[0] );
		
		a_00  = _mm256_load_ps( &A[0+lda*0] );
		temp  = _mm256_mul_ps( a_00, x_n_0 );
		y_n_0 = _mm256_add_ps( y_n_0, temp );
		temp  = _mm256_mul_ps( a_00, x_t_0 );
		y_t_0 = _mm256_add_ps( y_t_0, temp );

		a_01  = _mm256_load_ps( &A[0+lda*1] );
		temp  = _mm256_mul_ps( a_01, x_n_1 );
		y_n_0 = _mm256_add_ps( y_n_0, temp );
		temp  = _mm256_mul_ps( a_01, x_t_0 );
		y_t_1 = _mm256_add_ps( y_t_1, temp );

		a_02  = _mm256_load_ps( &A[0+lda*2] );
		temp  = _mm256_mul_ps( a_02, x_n_2 );
		y_n_0 = _mm256_add_ps( y_n_0, temp );
		temp  = _mm256_mul_ps( a_02, x_t_0 );
		y_t_2 = _mm256_add_ps( y_t_2, temp );

		a_03  = _mm256_load_ps( &A[0+lda*3] );
		temp  = _mm256_mul_ps( a_03, x_n_3 );
		y_n_0 = _mm256_add_ps( y_n_0, temp );
		temp  = _mm256_mul_ps( a_03, x_t_0 );
		y_t_3 = _mm256_add_ps( y_t_3, temp );
		
		_mm256_storeu_ps( &y_n[0], y_n_0 );
		

		A   += sda*lda;
		y_n += 8;
		x_t += 8;

		}
	
	if(k<kmax) // it can be only k_left = {1, 2, 3, 4, 5, 6, 7}
		{
		
		k_left = kmax-k;

		k_left_d = 8.0 - k_left;

/*		y_n_0 = _mm_load_ps( &y_n[0] );*/
/*		y_n_0 = _mm_setzero_ps();*/
		x_t_0 = _mm256_loadu_ps( &x_t[0] );
		x_t_0 = _mm256_blendv_ps( x_t_0, zeros, _mm256_sub_ps( mask, _mm256_broadcast_ss( &k_left_d) ) );
		
/*printf("\nk_left2 = %d\n", k_left, kmax, k);*/
		a_00  = _mm256_load_ps( &A[0+lda*0] );
/*printf("\nk_left2 = %d\n", k_left);*/
		a_01  = _mm256_load_ps( &A[0+lda*1] );
		a_02  = _mm256_load_ps( &A[0+lda*2] );
		a_03  = _mm256_load_ps( &A[0+lda*3] );
		
/*		temp  = _mm256_mul_ps( a_00, x_n_0 );*/
/*		y_n_0 = _mm256_add_ps( y_n_0, temp );*/
		y_n_0 = _mm256_mul_ps( a_00, x_n_0 );
		temp  = _mm256_mul_ps( a_00, x_t_0 );
		y_t_0 = _mm256_add_ps( y_t_0, temp );
		temp  = _mm256_mul_ps( a_01, x_n_1 );
		y_n_0 = _mm256_add_ps( y_n_0, temp );
		temp  = _mm256_mul_ps( a_01, x_t_0 );
		y_t_1 = _mm256_add_ps( y_t_1, temp );
		temp  = _mm256_mul_ps( a_02, x_n_2 );
		y_n_0 = _mm256_add_ps( y_n_0, temp );
		temp  = _mm256_mul_ps( a_02, x_t_0 );
		y_t_2 = _mm256_add_ps( y_t_2, temp );
		temp  = _mm256_mul_ps( a_03, x_n_3 );
		y_n_0 = _mm256_add_ps( y_n_0, temp );
		temp  = _mm256_mul_ps( a_03, x_t_0 );
		y_t_3 = _mm256_add_ps( y_t_3, temp );
		
		y_n_0 = _mm256_blendv_ps( y_n_0, zeros, _mm256_sub_ps( mask, _mm256_broadcast_ss( &k_left_d) ) );
		x_t_0 = _mm256_loadu_ps( &y_n[0] );
		y_n_0 = _mm256_add_ps( y_n_0, x_t_0 );
		_mm256_storeu_ps( &y_n[0], y_n_0 );
/*		_mm256_maskstore_ps( &y_n[0], (__m256i) _mm256_sub_ps( mask, _mm256_broadcast_ss( &k_left_d) ), y_n_0 );*/
	
/*		_mm256_storeu_ps( temp_space, y_n_0 );*/
/*		for(ii=0; ii<k_left; ii++)*/
/*			y_n[ii] = temp_space[ii];*/

/*		A   += 1;*/
/*		y_n += 1;*/
/*		x_t += 1;*/
		
		}

	// reduction
	__m128
		z_0, z_1;

	y_t_0 = _mm256_hadd_ps(y_t_0, y_t_1);
	y_t_2 = _mm256_hadd_ps(y_t_2, y_t_3);

	y_t_0 = _mm256_hadd_ps(y_t_0, y_t_2);

	y_t_1 = _mm256_permute2f128_ps(y_t_0, y_t_0, 0x01);
	
	z_0 = _mm256_castps256_ps128(y_t_0);
	z_1 = _mm256_castps256_ps128(y_t_1);
	
	z_1 = _mm_add_ps(z_0, z_1);

	if(alg==1)
		{
		z_0 = _mm_loadu_ps( &y_t[0] );

		z_0 = _mm_add_ps(z_0, z_1);

		_mm_storeu_ps( &y_t[0], z_0 );
		}
	else // alg==-1
		{
		z_0 = _mm_loadu_ps( &y_t[0] );

		z_0 = _mm_sub_ps(z_0, z_1);

		_mm_storeu_ps( &y_t[0], z_0 );
		}
	
	}