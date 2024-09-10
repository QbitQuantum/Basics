/* ------------------------------------------------------------------------- */
void primitives_init_add_opt(
	primitives_t *prims)
{
#ifdef WITH_IPP
	prims->add_16s = (__add_16s_t) ippsAdd_16s;
#elif defined(WITH_SSE2)
	if (IsProcessorFeaturePresent(PF_SSE2_INSTRUCTIONS_AVAILABLE)
			&& IsProcessorFeaturePresent(PF_SSE3_INSTRUCTIONS_AVAILABLE))	/* for LDDQU */
	{
		prims->add_16s = sse3_add_16s;
	}
#endif
}