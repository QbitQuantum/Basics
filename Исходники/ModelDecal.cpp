/*
=====================
R_CopyDecalSurface
=====================
*/
static void R_CopyDecalSurface( idDrawVert * verts, int numVerts, triIndex_t * indexes, int numIndexes,
									const decal_t * decal, const float fadeColor[4] ) {
	assert_16_byte_aligned( &verts[numVerts] );
	assert_16_byte_aligned( &indexes[numIndexes] );
	assert_16_byte_aligned( decal->indexes );
	assert_16_byte_aligned( decal->verts );
	assert( ( ( decal->numVerts * sizeof( idDrawVert ) ) & 15 ) == 0 );
	assert( ( ( decal->numIndexes * sizeof( triIndex_t ) ) & 15 ) == 0 );
	assert_16_byte_aligned( fadeColor );


	const __m128i vector_int_num_verts = _mm_shuffle_epi32( _mm_cvtsi32_si128( numVerts ), 0 );
	const __m128i vector_short_num_verts = _mm_packs_epi32( vector_int_num_verts, vector_int_num_verts );
	const __m128 vector_fade_color = _mm_load_ps( fadeColor );
	const __m128i vector_color_mask = _mm_set_epi32( 0, -1, 0, 0 );

	// copy vertices and apply depth/time based fading
	assert_offsetof( idDrawVert, color, 6 * 4 );
	for ( int i = 0; i < decal->numVerts; i++ ) {
		const idDrawVert &srcVert = decal->verts[i];
		idDrawVert &dstVert = verts[numVerts + i];

		__m128i v0 = _mm_load_si128( (const __m128i *)( (byte *)&srcVert +  0 ) );
		__m128i v1 = _mm_load_si128( (const __m128i *)( (byte *)&srcVert + 16 ) );
		__m128 depthFade = _mm_splat_ps( _mm_load_ss( decal->vertDepthFade + i ), 0 );

		__m128 timeDepthFade = _mm_mul_ps( depthFade, vector_fade_color );
		__m128i colorInt = _mm_cvtps_epi32( timeDepthFade );
		__m128i colorShort = _mm_packs_epi32( colorInt, colorInt );
		__m128i colorByte = _mm_packus_epi16( colorShort, colorShort );
		v1 = _mm_or_si128( v1, _mm_and_si128( colorByte, vector_color_mask ) );

		_mm_stream_si128( (__m128i *)( (byte *)&dstVert +  0 ), v0 );
		_mm_stream_si128( (__m128i *)( (byte *)&dstVert + 16 ), v1 );
	}

	// copy indexes
	assert( ( decal->numIndexes & 7 ) == 0 );
	assert( sizeof( triIndex_t ) == 2 );
	for ( int i = 0; i < decal->numIndexes; i += 8 ) {
		__m128i vi = _mm_load_si128( (const __m128i *)&decal->indexes[i] );

		vi = _mm_add_epi16( vi, vector_short_num_verts );

		_mm_stream_si128( (__m128i *)&indexes[numIndexes + i], vi );
	}

	_mm_sfence();

}