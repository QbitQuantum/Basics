void test(const std::string& s, F f)
{
	const int M = 100;
	uint64_t x = 0;
	Xbyak::util::Clock clk;
	for (int i = 0; i < M; i++) {
		clk.begin();
		x += f((const uint8_t*)s.c_str(), s.size());
		clk.end();
	}
	printf("x=%16lld, %.2fclk\n", (long long)x, clk.getClock() / double(M) / s.size());
}