bool opt_copy_stream_to_stream( x42memStream_t *dest, x42memStream_t *src,
	size_t elemSize, uint numElems, x42opts_t *opts )
{
	REF_PARAM( opts );
	
	if( (opts->caps & OPT_SSE2) &&
		elemSize <= sizeof( __m128 ) &&
		stream_is_aligned( src ) && stream_pad_ok( src, elemSize ) &&
		stream_is_aligned( dest ) && stream_pad_ok( dest, elemSize ) )
	{ 
		uint i; 

		size_t is = src->stride; 
		size_t os = dest->stride; 

		const __m128i * RESTRICT pi = (__m128i*)src->pStreamZero; 
		__m128i * RESTRICT po = (__m128i*)dest->pStreamZero; 

		for( i = 0; i < numElems; i++ ) 
		{ 
			__m128i v = _mm_load_si128( pi ); 
			_mm_stream_si128( po, v ); 

			pi = (__m128i*)((byte*)pi + is); 
			po = (__m128i*)((byte*)po + os); 
		} 

		_mm_sfence(); 

		return true;
	}