void test(size_t n, bool doPut, F pred)
{
	IntVec iv;
	PtrVec pv;
	init(iv, pv, n);
	if (doPut) put(pv);
	Xbyak::util::Clock clk;
	clk.begin();
	std::sort(pv.begin(), pv.end(), pred);
	clk.end();
	int sum = std::accumulate(iv.begin(), iv.end(), 0);
	printf("clk=%.2fclk, sum=%d\n", clk.getClock() / double(n), sum);
	if (doPut) put(pv);
}