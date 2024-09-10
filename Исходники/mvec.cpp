int dist( unsigned char *p1, unsigned char *p2, int lx, int distlim, int block_height )
{
	if (block_height == 8) {
		__m128i a, b, r;

		a = _mm_load_si128 ((__m128i*)p1 +  0);
		b = _mm_loadu_si128((__m128i*)p2 +  0);
		r = _mm_sad_epu8(a, b);
		
		a = _mm_load_si128 ((__m128i*)(p1 + lx));
		b = _mm_loadu_si128((__m128i*)(p2 + lx));
		r = _mm_add_epi32(r, _mm_sad_epu8(a, b));
		
		a = _mm_load_si128 ((__m128i*)(p1 + 2*lx));
		b = _mm_loadu_si128((__m128i*)(p2 + 2*lx));
		r = _mm_add_epi32(r, _mm_sad_epu8(a, b));
		
		a = _mm_load_si128 ((__m128i*)(p1 + 3*lx));
		b = _mm_loadu_si128((__m128i*)(p2 + 3*lx));
		r = _mm_add_epi32(r, _mm_sad_epu8(a, b));
		
		a = _mm_load_si128 ((__m128i*)(p1 + 4*lx));
		b = _mm_loadu_si128((__m128i*)(p2 + 4*lx));
		r = _mm_add_epi32(r, _mm_sad_epu8(a, b));
		
		a = _mm_load_si128 ((__m128i*)(p1 + 5*lx));
		b = _mm_loadu_si128((__m128i*)(p2 + 5*lx));
		r = _mm_add_epi32(r, _mm_sad_epu8(a, b));
		
		a = _mm_load_si128 ((__m128i*)(p1 + 6*lx));
		b = _mm_loadu_si128((__m128i*)(p2 + 6*lx));
		r = _mm_add_epi32(r, _mm_sad_epu8(a, b));
		
		a = _mm_load_si128 ((__m128i*)(p1 + 7*lx));
		b = _mm_loadu_si128((__m128i*)(p2 + 7*lx));
		r = _mm_add_epi32(r, _mm_sad_epu8(a, b));
		return _mm_extract_epi16(r, 0) + _mm_extract_epi16(r, 4);;
	}
	
	int s = 0;
	for(int i=0;i<block_height;i++)
	{
		/*
		s += motion_lookup[p1[0]][p2[0]];
		s += motion_lookup[p1[1]][p2[1]];
		s += motion_lookup[p1[2]][p2[2]];
		s += motion_lookup[p1[3]][p2[3]];
		s += motion_lookup[p1[4]][p2[4]];
		s += motion_lookup[p1[5]][p2[5]];
		s += motion_lookup[p1[6]][p2[6]];
		s += motion_lookup[p1[7]][p2[7]];
		s += motion_lookup[p1[8]][p2[8]];
		s += motion_lookup[p1[9]][p2[9]];
		s += motion_lookup[p1[10]][p2[10]];
		s += motion_lookup[p1[11]][p2[11]];
		s += motion_lookup[p1[12]][p2[12]];
		s += motion_lookup[p1[13]][p2[13]];
		s += motion_lookup[p1[14]][p2[14]];
		s += motion_lookup[p1[15]][p2[15]];*/
		
		__m128i a = _mm_load_si128((__m128i*)p1);
		__m128i b = _mm_loadu_si128((__m128i*)p2);
		__m128i r = _mm_sad_epu8(a, b);
		s += _mm_extract_epi16(r, 0) + _mm_extract_epi16(r, 4);

		if (s > distlim)	break;

		p1 += lx;
		p2 += lx;
	}
	return s;
}