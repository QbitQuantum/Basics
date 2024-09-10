		size_t DefaultMovable::size(const void* ptr)
		{
			return HeapSize(GetProcessHeap(), 0, ptr);
		}