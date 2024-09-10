static int getCpuInfo(  )
{
#ifdef _WIN32
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	if (si.dwNumberOfProcessors > Config.Threads) {
		Config.Threads = si.dwNumberOfProcessors;
	}

	int popcnt = 0;
#if POPCNT && _MSC_VER
	__try {
		popcnt = _mm_popcnt_u32(1);
	}
	__except (filterFunc(GetExceptionCode())) {
		popcnt = 0;
	}
#elif POPCNT
	popcnt = _mm_popcnt_u32(1);
#endif

	printf("Cpu cores = %ld, SSE4 with Popcnt = %d\n",
		si.dwNumberOfProcessors, popcnt);

	return si.dwNumberOfProcessors;
#endif
}