void GSRasterizerList::Draw(const GSRasterizerData* data)
{
	*m_sync = 0;

	m_stats.Reset();

	__int64 start = __rdtsc();

	POSITION pos = GetTailPosition();

	while(pos)
	{
		GetPrev(pos)->Draw(data);
	}

	while(*m_sync)
	{
		_mm_pause();
	}

	m_stats.ticks = __rdtsc() - start;

	pos = GetHeadPosition();

	while(pos)
	{
		GSRasterizerStats s;

		GetNext(pos)->GetStats(s);

		m_stats.pixels += s.pixels;
		m_stats.prims = max(m_stats.prims, s.prims);
	}
}