uint64_t bench(const uint64_t *block, size_t blockNum, size_t n, size_t bitLen, double baseClk, bool useSelect)
{
	const T sbv(block, blockNum);
	uint64_t ret = 0;
	Xbyak::util::Clock clk;
#ifdef USE_C11
	std::uniform_int_distribution<uint64_t> dist(0, (1ULL << bitLen) - 1);
#else
	XorShift128 r;
	const uint64_t mask = (1ULL << bitLen) - 1;
#endif
	const int lp = 5;
	for (int j = 0; j < lp; j++) {
		clk.begin();
		for (size_t i = 0; i < n; i++) {
#ifdef USE_C11
			uint64_t v = dist(g_rg);
#else
			uint64_t v = r.get64();
			v &= mask;
#endif
			ret += sbv.rank1(v);
		}
		clk.end();
	}
	printf("%11lld ret %08x %6.2f clk(%6.2f)\n", 1LL << bitLen, (int)ret, (double)clk.getClock() / double(n) / lp - baseClk, baseClk);
	if (useSelect) {
		clk.clear();
		const size_t maxNum = sbv.rank1(blockNum * 64 - 1);
		for (int j = 0; j < lp; j++) {
			clk.begin();
			for (size_t i = 0; i < n; i++) {
#ifdef USE_C11
				uint64_t v = dist(g_rg);
#else
				uint64_t v = r.get64();
				v %= maxNum;
#endif
				ret += sbv.select1(v);
			}
			clk.end();
		}
		printf("%11lld ret %08x %6.2f clk(%6.2f)\n", 1LL << bitLen, (int)ret, (double)clk.getClock() / double(n) / lp - baseClk, baseClk);
	}
	return ret;
}