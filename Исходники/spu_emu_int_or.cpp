inline GPR_t si_ori( GPR_t RA, int64_t IMM )
{
	return _mm_or_ps( RA, _mm_castsi128_ps( _mm_set1_epi32( (int32_t)IMM ) ) );
}