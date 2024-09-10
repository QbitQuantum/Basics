void CMatrixMultPoint2D::kernelSSE( float* imgIn, float* imgOut, __m128& m0, __m128& m1, __m128& m2, int i )
{
#if 0
	__m128 *pSrcPos = (__m128*)imgIn;
	__m64 *pDestPos = (__m64*)imgOut;

	for (int j=0;j<SIZE_WIDTH/2 ;j++)
	{
		__m128 vIn0x, vIn0y, vIn1x, vIn1y;

		int index = j+i*SIZE_WIDTH/2;
		vIn0x = __MM_SELECT( pSrcPos[index], 0); 
		vIn0y = __MM_SELECT( pSrcPos[index], 1); 

		__m128 vOut0;
		__m128 tmp00, tmp01;
		tmp00 = _mm_mul_ps( m0, vIn0x );
		tmp01 = _mm_mul_ps( m1, vIn0y );

		vOut0 = _mm_add_ps( tmp00, tmp01 );
		vOut0 = _mm_add_ps( vOut0, m2 );
		_mm_storel_pi( (__m64*)(&pDestPos[index*2]), vOut0 );
		
		vIn1x = __MM_SELECT( pSrcPos[index], 2); 
		vIn1y = __MM_SELECT( pSrcPos[index], 3); 
		__m128 vOut1;
		__m128 tmp10, tmp11;
		tmp10 = _mm_mul_ps( m0, vIn1x );
		tmp11 = _mm_mul_ps( m1, vIn1y );

		vOut1 = _mm_add_ps( tmp10, tmp11 );
		vOut1 = _mm_add_ps(    vOut1, m2 );
		_mm_storel_pi( (__m64*)(&pDestPos[index*2+1]), vOut1 );
		
	}
#else
	__m128 *pSrcPos = (__m128*)imgIn;
	__m128 *pDestPos = (__m128*)imgOut;
	int nOffset = i*SIZE_WIDTH/2;

#if OPTIMIZE_OMP && OPTIMIZE_INNER_LOOP
#pragma omp parallel for //shared(nOffset)
#endif
	for (int j=0;j<SIZE_WIDTH/2 ;j++)
	{
		
		// (x1,x1,x2,x2)  (y1,y1,y2,y2)
		__m128 vIn = pSrcPos[j+nOffset];

		__m128 vInx = _mm_shuffle_ps( vIn, vIn, _MM_SHUFFLE(2,2,0,0) );
		__m128 vIny = _mm_shuffle_ps( vIn, vIn, _MM_SHUFFLE(3,3,1,1) );

		__m128 tmp00 = _mm_mul_ps( m0, vInx );
		__m128 tmp01 = _mm_mul_ps( m1, vIny );

		__m128 vOut0 = _mm_add_ps( tmp00, tmp01 );
		vOut0 = _mm_add_ps( vOut0, m2 );
		
		pDestPos[j+nOffset] = vOut0 ;


	}
#endif

}