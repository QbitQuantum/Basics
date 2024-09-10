// inverted diagonal !!!
void kernel_spotrf_strsv_1x1_lib4(int kmax, float *A, int sda, int *info)
	{
	
	const int lda = 4;
	
	__m128
		zeros, ones,
		a_00,
		b_00_10;
	
	zeros = _mm_set_ss( 0.0 );

	a_00 = _mm_load_ss( &A[0+lda*0] );
	if( _mm_comile_ss ( a_00, zeros ) ) { *info = 1; return; }
	a_00 = _mm_sqrt_ss( a_00 );
	ones = _mm_set_ss( 1.0 );
	a_00 = _mm_div_ss( ones, a_00 );
	_mm_store_ss( &A[0+lda*0], a_00 );
	
	if(kmax<=0)
		return;
	
	// strsv


	a_00 = _mm_shuffle_ps( a_00, a_00, 0 );
	
	int k, kna;
	
	float
		*AA;
	
	AA = A + 1;
	k = 0;

	// clean up unaligned stuff at the beginning
	kna = 3;
	if(kmax<kna)
		kna = kmax;

	for(; k<kna; k++)
		{
		b_00_10 = _mm_load_ss( &AA[lda*0] );

		b_00_10 = _mm_mul_ss( b_00_10, a_00 );
		_mm_store_ss( &AA[lda*0], b_00_10 );

		AA += 1;
		}

	for(; k<kmax-3; k+=4)
		{

		AA += lda*(sda-1);
		
		b_00_10 = _mm_load_ps( &AA[0+lda*0] );

		b_00_10 = _mm_mul_ps( b_00_10, a_00 );
		_mm_store_ps( &AA[0+lda*0], b_00_10 );

		AA += 4;
		
		}

	AA += lda*(sda-1);

	for(; k<kmax; k++)
		{
		b_00_10 = _mm_load_ss( &AA[lda*0] );

		b_00_10 = _mm_mul_ss( b_00_10, a_00 );
		_mm_store_ss( &AA[lda*0], b_00_10 );

		AA += 1;
		}
	
	}