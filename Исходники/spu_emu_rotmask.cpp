void spu_rotmahi( SPU_t* SPU, SPU_INSTRUCTION op )
{
	const int s = 0x1f&( 0 - SignExtend(op.RI7.I7, 7) );
	SPU->GPR[op.RI7.RT] = _mm_castsi128_ps( _mm_srai_epi16( _mm_castps_si128( SPU->GPR[op.RI7.RA] ), s ) );
}