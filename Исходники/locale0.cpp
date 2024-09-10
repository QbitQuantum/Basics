	void * operator new(size_t _Size)
		{	// replace operator new
		void * _Ptr = _malloc_dbg(_Size > 0 ? _Size : 1, _CRT_BLOCK, __FILE__, __LINE__);
		if (!_Ptr)
			_Xbad_alloc();
		return (_Ptr);
		}