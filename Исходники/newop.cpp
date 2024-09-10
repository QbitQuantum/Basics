void *__CRTDECL operator new(size_t count) _THROW1(_STD bad_alloc)
	{	// try to allocate size bytes
	void *p;
	while ((p = malloc(count)) == 0)
		if (_callnewh(count) == 0)
			{	// report no memory
			_STD _Xbad_alloc();
			}
	return (p);
	}