	void epub_sys_cache_flush(void* start, long len)
	{
#if EPUB_CPU(X86) || EPUB_CPU(X64)
		if (start == nullptr || len <= 0)
			return;

		unsigned char* p = reinterpret_cast<unsigned char*>(start);

		// ensure all reads/write complete before the next instruction
		_mm_mfence();

		// ensure the last line is flushed
		_mm_clflush(p + (len - 1));

		// flush all cache lines. lines are 64 bytes on both architectures
		while (len > 0)
		{
			_mm_clflush(p);
			p += 64;
			len -= 64;
		}
#elif EPUB_CPU(ARM)
		// no idea...
#endif
	}