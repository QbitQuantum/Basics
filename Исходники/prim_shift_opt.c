/* ------------------------------------------------------------------------- */
void primitives_init_shift_opt(primitives_t *prims)
{
#if defined(WITH_IPP)
	prims->lShiftC_16s = (__lShiftC_16s_t) ippsLShiftC_16s;
	prims->rShiftC_16s = (__rShiftC_16s_t) ippsRShiftC_16s;
	prims->lShiftC_16u = (__lShiftC_16u_t) ippsLShiftC_16u;
	prims->rShiftC_16u = (__rShiftC_16u_t) ippsRShiftC_16u;
#elif defined(WITH_SSE2)
	if (IsProcessorFeaturePresent(PF_SSE2_INSTRUCTIONS_AVAILABLE)
			&& IsProcessorFeaturePresent(PF_SSE3_INSTRUCTIONS_AVAILABLE))
	{
		prims->lShiftC_16s = sse2_lShiftC_16s;
		prims->rShiftC_16s = sse2_rShiftC_16s;
		prims->lShiftC_16u = sse2_lShiftC_16u;
		prims->rShiftC_16u = sse2_rShiftC_16u;
	}
#endif
}