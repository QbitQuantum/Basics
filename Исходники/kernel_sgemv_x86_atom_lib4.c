void kernel_sgemv_t_1_lib4(int kmax, int kna, float *A, int sda, float *x, float *y, int alg)
	{
	if(kmax<=0) return;
	
	const int lda = 4;
	
	int k;
	int ka = kmax-kna; // number from aligned positon
	
	__m128
		a_00_10_20_30,
		x_0_1_2_3,
		y_0, y_1;
	
	y_0 = _mm_setzero_ps();	

	k = 0;
	if(kna>0)
		{
		for(; k<kna; k++)
			{
		
			x_0_1_2_3 = _mm_load_ss( &x[0] );

			a_00_10_20_30 = _mm_load_ss( &A[0+lda*0] );
		
/*			y_0 += a_00_10_20_30 * x_0_1_2_3;*/
			a_00_10_20_30 = _mm_mul_ss( a_00_10_20_30, x_0_1_2_3 );
			y_0 = _mm_add_ss( y_0, a_00_10_20_30 );
		
			x += 1;
			A += 1;

			}

		A += (sda-1)*lda;
		}

	k = 0;
	for(; k<ka-3; k+=4)
		{
		
		x_0_1_2_3 = _mm_loadu_ps( &x[0] );

		a_00_10_20_30 = _mm_load_ps( &A[0+lda*0] );
		
/*		y_0 += a_00_10_20_30 * x_0_1_2_3;*/
		a_00_10_20_30 = _mm_mul_ps( a_00_10_20_30, x_0_1_2_3 );
		y_0 = _mm_add_ps( y_0, a_00_10_20_30 );
		
		x += 4;
		A += 4;

		A += (sda-1)*lda;

		}
	for(; k<ka; k++)
		{
		
		x_0_1_2_3 = _mm_load_ss( &x[0] );

		a_00_10_20_30 = _mm_load_ss( &A[0+lda*0] );
	
/*		y_0 += a_00_10_20_30 * x_0_1_2_3;*/
		a_00_10_20_30 = _mm_mul_ss( a_00_10_20_30, x_0_1_2_3 );
		y_0 = _mm_add_ss( y_0, a_00_10_20_30 );
	
		x += 1;
		A += 1;
		
		}

	__m128
		y_0_1_2_3;

	y_1 = _mm_setzero_ps();
	y_0 = _mm_hadd_ps(y_0, y_1);
	y_0 = _mm_hadd_ps(y_0, y_1);

	if(alg==0)
		{
		_mm_store_ss(&y[0], y_0);
		}
	else if(alg==1)
		{
		y_0_1_2_3 = _mm_load_ss( &y[0] );

		y_0_1_2_3 = _mm_add_ss(y_0_1_2_3, y_0);
	
		_mm_store_ss(&y[0], y_0_1_2_3);
		}
	else // alg==-1
		{
		y_0_1_2_3 = _mm_load_ss( &y[0] );

		y_0_1_2_3 = _mm_sub_ss(y_0_1_2_3, y_0);
	
		_mm_store_ss(&y[0], y_0_1_2_3);
		}

	}