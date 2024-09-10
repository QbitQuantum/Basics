void *operator new(size_t size, const std::nothrow_t&) _THROW0()
	{	// try to allocate size bytes
	void *p;
	while ((p = malloc(size)) == 0)
		{	// buy more memory or return null pointer
		_TRY_BEGIN
			if (_callnewh(size) == 0)
				break;
		_CATCH(std::bad_alloc)
			return (0);
		_CATCH_END
		}
	return (p);
	}