	inline int64_t to_int64(const wchar_t* in, int base = 10)
	{
#ifdef _MSC_VER
		UNUSED(base);
		return _wtoi64(in);
#else
		wchar_t* end_ptr;
		return ::wcstoll(in, &end_ptr, base);
#endif
	}