/*
====================
R_OverlayPointCullSkinned
====================
*/
static void R_OverlayPointCullSkinned( byte* cullBits, halfFloat_t* texCoordS, halfFloat_t* texCoordT, const idPlane* planes, const idDrawVert* verts, const int numVerts, const idJointMat* joints )
{
	assert_16_byte_aligned( cullBits );
	assert_16_byte_aligned( texCoordS );
	assert_16_byte_aligned( texCoordT );
	assert_16_byte_aligned( verts );
	
#if defined(USE_INTRINSICS)
	idODSStreamedArray< idDrawVert, 16, SBT_DOUBLE, 4 > vertsODS( verts, numVerts );
	
	const __m128 vector_float_zero	= { 0.0f, 0.0f, 0.0f, 0.0f };
	const __m128 vector_float_one	= { 1.0f, 1.0f, 1.0f, 1.0f };
	const __m128i vector_int_mask0	= _mm_set1_epi32( 1 << 0 );
	const __m128i vector_int_mask1	= _mm_set1_epi32( 1 << 1 );
	const __m128i vector_int_mask2	= _mm_set1_epi32( 1 << 2 );
	const __m128i vector_int_mask3	= _mm_set1_epi32( 1 << 3 );
	
	const __m128 p0 = _mm_loadu_ps( planes[0].ToFloatPtr() );
	const __m128 p1 = _mm_loadu_ps( planes[1].ToFloatPtr() );
	
	const __m128 p0X = _mm_splat_ps( p0, 0 );
	const __m128 p0Y = _mm_splat_ps( p0, 1 );
	const __m128 p0Z = _mm_splat_ps( p0, 2 );
	const __m128 p0W = _mm_splat_ps( p0, 3 );
	
	const __m128 p1X = _mm_splat_ps( p1, 0 );
	const __m128 p1Y = _mm_splat_ps( p1, 1 );
	const __m128 p1Z = _mm_splat_ps( p1, 2 );
	const __m128 p1W = _mm_splat_ps( p1, 3 );
	
	for( int i = 0; i < numVerts; )
	{
	
		const int nextNumVerts = vertsODS.FetchNextBatch() - 4;
		
		for( ; i <= nextNumVerts; i += 4 )
		{
			const __m128 v0 = LoadSkinnedDrawVertPosition( vertsODS[i + 0], joints );
			const __m128 v1 = LoadSkinnedDrawVertPosition( vertsODS[i + 1], joints );
			const __m128 v2 = LoadSkinnedDrawVertPosition( vertsODS[i + 2], joints );
			const __m128 v3 = LoadSkinnedDrawVertPosition( vertsODS[i + 3], joints );
			
			const __m128 r0 = _mm_unpacklo_ps( v0, v2 );	// v0.x, v2.x, v0.z, v2.z
			const __m128 r1 = _mm_unpackhi_ps( v0, v2 );	// v0.y, v2.y, v0.w, v2.w
			const __m128 r2 = _mm_unpacklo_ps( v1, v3 );	// v1.x, v3.x, v1.z, v3.z
			const __m128 r3 = _mm_unpackhi_ps( v1, v3 );	// v1.y, v3.y, v1.w, v3.w
			
			const __m128 vX = _mm_unpacklo_ps( r0, r2 );	// v0.x, v1.x, v2.x, v3.x
			const __m128 vY = _mm_unpackhi_ps( r0, r2 );	// v0.y, v1.y, v2.y, v3.y
			const __m128 vZ = _mm_unpacklo_ps( r1, r3 );	// v0.z, v1.z, v2.z, v3.z
			
			const __m128 d0 = _mm_madd_ps( vX, p0X, _mm_madd_ps( vY, p0Y, _mm_madd_ps( vZ, p0Z, p0W ) ) );
			const __m128 d1 = _mm_madd_ps( vX, p1X, _mm_madd_ps( vY, p1Y, _mm_madd_ps( vZ, p1Z, p1W ) ) );
			const __m128 d2 = _mm_sub_ps( vector_float_one, d0 );
			const __m128 d3 = _mm_sub_ps( vector_float_one, d1 );
			
			__m128i flt16S = FastF32toF16( __m128c( d0 ) );
			__m128i flt16T = FastF32toF16( __m128c( d1 ) );
			
			_mm_storel_epi64( ( __m128i* )&texCoordS[i], flt16S );
			_mm_storel_epi64( ( __m128i* )&texCoordT[i], flt16T );
			
			__m128i c0 = __m128c( _mm_cmplt_ps( d0, vector_float_zero ) );
			__m128i c1 = __m128c( _mm_cmplt_ps( d1, vector_float_zero ) );
			__m128i c2 = __m128c( _mm_cmplt_ps( d2, vector_float_zero ) );
			__m128i c3 = __m128c( _mm_cmplt_ps( d3, vector_float_zero ) );
			
			c0 = _mm_and_si128( c0, vector_int_mask0 );
			c1 = _mm_and_si128( c1, vector_int_mask1 );
			c2 = _mm_and_si128( c2, vector_int_mask2 );
			c3 = _mm_and_si128( c3, vector_int_mask3 );
			
			c0 = _mm_or_si128( c0, c1 );
			c2 = _mm_or_si128( c2, c3 );
			c0 = _mm_or_si128( c0, c2 );
			
			c0 = _mm_packs_epi32( c0, c0 );
			c0 = _mm_packus_epi16( c0, c0 );
			
			*( unsigned int* )&cullBits[i] = _mm_cvtsi128_si32( c0 );
		}
	}
	
#else
	
	idODSStreamedArray< idDrawVert, 16, SBT_DOUBLE, 1 > vertsODS( verts, numVerts );
	
	for( int i = 0; i < numVerts; )
	{
	
		const int nextNumVerts = vertsODS.FetchNextBatch() - 1;
	
		for( ; i <= nextNumVerts; i++ )
		{
			const idVec3 transformed = Scalar_LoadSkinnedDrawVertPosition( vertsODS[i], joints );
	
			const float d0 = planes[0].Distance( transformed );
			const float d1 = planes[1].Distance( transformed );
			const float d2 = 1.0f - d0;
			const float d3 = 1.0f - d1;
	
			halfFloat_t s = Scalar_FastF32toF16( d0 );
			halfFloat_t t = Scalar_FastF32toF16( d1 );
	
			texCoordS[i] = s;
			texCoordT[i] = t;
	
			byte bits;
			bits  = IEEE_FLT_SIGNBITSET( d0 ) << 0;
			bits |= IEEE_FLT_SIGNBITSET( d1 ) << 1;
			bits |= IEEE_FLT_SIGNBITSET( d2 ) << 2;
			bits |= IEEE_FLT_SIGNBITSET( d3 ) << 3;
	
			cullBits[i] = bits;
		}
	}
	
#endif
}