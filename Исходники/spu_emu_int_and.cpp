inline GPR_t si_nand( GPR_t RA, GPR_t RB )
{
	return _mm_andnot_ps( _mm_and_ps( RA, RB ), _mm_castsi128_ps( _mm_set1_epi32( 0xffffffff ) ) );
}