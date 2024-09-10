void test(const char *msg, void (*f)())
{
	Xbyak::util::Clock clk;
	counter = 0;
	clk.begin();
	f();
	clk.end();
	printf("%s %.2f clk/loop counter=%lld\n", msg, clk.getClock() / double(clk.getCount() * N), (long long)counter);
}