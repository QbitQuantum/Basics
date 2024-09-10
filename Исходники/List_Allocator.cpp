void FixedSizeAllocator::FreePage(void *page)
{
	switch (m_arena)
	{
	case MEMORY_ARENA_STACK: _freea(page); break;
	case MEMORY_ARENA_HEAP:  free(page); break;
	}
}