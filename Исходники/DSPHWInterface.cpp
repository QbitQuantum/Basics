// TODO: These should eat clock cycles.
static void gdsp_ddma_in(u16 dsp_addr, u32 addr, u32 size)
{
	u8* dst = ((u8*)g_dsp.dram);

#if _M_SSE >= 0x301
	if (cpu_info.bSSSE3 && !(size % 16))
	{
		for (u32 i = 0; i < size; i += 16)
		{
			_mm_storeu_si128((__m128i *)&dst[dsp_addr + i], _mm_shuffle_epi8(_mm_loadu_si128((__m128i *)&g_dsp.cpu_ram[(addr + i) & 0x7FFFFFFF]), s_mask));
		}
	}
	else
#endif
	{
		for (u32 i = 0; i < size; i += 2)
		{
			*(u16*)&dst[dsp_addr + i] = Common::swap16(*(const u16*)&g_dsp.cpu_ram[(addr + i) & 0x7FFFFFFF]);
		}
	}
	INFO_LOG(DSPLLE, "*** ddma_in RAM (0x%08x) -> DRAM_DSP (0x%04x) : size (0x%08x)", addr, dsp_addr / 2, size);
}