inline GPR_t si_xorbi( GPR_t RA, int64_t IMM )
{
	return _mm_xor_ps( RA, _mm_castsi128_ps( _mm_set1_epi8((uint8_t)IMM) ) );
}