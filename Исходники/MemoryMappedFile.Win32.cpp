	void MemoryMappedFile::PrefetchRange( Range<const char*> memoryRange ) const {
#	if( WIN8_MEMORY_MAPPED_FILE_AVAILABLE )
		WIN32_MEMORY_RANGE_ENTRY	ranges[] = { { const_cast<char*>( memoryRange.first ), memoryRange.GetSize() } };

		PrefetchVirtualMemory( GetCurrentProcess(), _countof( ranges ), ranges, 0 );
#	else
		for( auto temp( memoryRange.Begin() ); temp < memoryRange.End(); temp += PrefetchStride ) {
		//	TODO: Is it possible to use prefetch instructions to avoid polluting the processor caches?
			register int readTarget = *reinterpret_cast<const int*>(temp);
		}
#	endif
	}