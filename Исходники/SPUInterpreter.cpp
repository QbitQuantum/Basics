void spu_interpreter::FRSQEST(SPUThread& CPU, spu_opcode_t op)
{
	const auto mask = _mm_castsi128_ps(_mm_set1_epi32(0x7fffffff));
	CPU.GPR[op.rt].vf = _mm_rsqrt_ps(_mm_and_ps(CPU.GPR[op.ra].vf, mask));
}