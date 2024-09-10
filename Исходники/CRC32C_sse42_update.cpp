void libmaus::digest::CRC32C_sse42::update(uint8_t const * t, size_t l) 
{
	#if defined(LIBMAUS_HAVE_SMMINTRIN_H) && defined(LIBMAUS_USE_ASSEMBLY) && defined(LIBMAUS_HAVE_x86_64) && defined(LIBMAUS_HAVE_i386)
	ctx = ~ctx;
		
	size_t const offset = reinterpret_cast<size_t>(t);
		
	// check for 3 LSB
	if ( offset & 7 )
	{
		// check for LSB
		if ( (offset & 1) && l )
		{
			ctx = _mm_crc32_u8(ctx, *t);
			t += 1;
			l -= 1;
		}
		// check for 2nd LSB
		if ( (offset & 2) && (l>=2) )
		{
			ctx = _mm_crc32_u16(ctx, *reinterpret_cast<uint16_t const *>(t));
			t += 2;
			l -= 2;			
		}	
		// check for 3rd LSB
		if ( (offset & 4) && l >= 4 )
		{
			ctx = _mm_crc32_u32(ctx, *reinterpret_cast<uint32_t const *>(t));
			t += 4;
			l -= 4;			
		}
	}
	
	uint64_t const * t64 = reinterpret_cast<uint64_t const *>(t);
	uint64_t const * const t64e = t64 + (l>>3);
	
	while ( t64 != t64e )
		ctx = _mm_crc32_u64(ctx, *(t64++));
		
	l &= 7;
	t = reinterpret_cast<uint8_t const *>(t64);
	
	if ( l >= 4 )
	{
		ctx = _mm_crc32_u32(ctx, *reinterpret_cast<uint32_t const *>(t));
		t += 4;
		l -= 4;	
	}
	if ( l >= 2 )
	{
		ctx = _mm_crc32_u16(ctx, *reinterpret_cast<uint16_t const *>(t));
		t += 2;
		l -= 2;	
	}
	if ( l )
	{
		ctx = _mm_crc32_u8(ctx, *t);
	}
	
	ctx = ~ctx;
	#endif
}