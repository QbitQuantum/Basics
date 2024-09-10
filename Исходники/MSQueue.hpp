	inline bool CAS(Ptr<T> &destination, const Ptr<T> &expected, const Ptr<T> &replacement)
	{
#if defined(ARCH_64)
		Ptr<T> ComparandResult;
		ComparandResult.N[0] = expected.N[0];
		ComparandResult.N[1] = expected.N[1];
		// NOTE: Requires VS.NET 2008 or newer
		return 1 == _InterlockedCompareExchange128((__int64*)destination.N, replacement.N[1],
												   replacement.N[0], (__int64*)ComparandResult.N);
#else
		return expected.N == _InterlockedCompareExchange64((LONGLONG*)&destination.N,
														   replacement.N, expected.N);
#endif
	}