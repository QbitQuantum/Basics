int main()
{
	const int count = 1000;
	Xbyak::util::Clock clk;
	Code c;
	void (*f)() = (void (*)())c.getCode();
	for (int i = 0; i < count; i++) {
		clk.begin();
		f();
		clk.end();
	}
	printf("%.3fclk\n", clk.getClock() / double(N) / clk.getCount());
}