	Win32GlobalHeapAllocator::Win32GlobalHeapAllocator( const Utf8Char* const name ) : Detail::Win32HeapAllocatorBase( reinterpret_cast<HANDLE>(_get_heap_handle()), name ) {}