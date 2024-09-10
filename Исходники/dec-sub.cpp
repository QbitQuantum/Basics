int main(int argc, char *argv[])
{
	int mode = argc == 1 ? -1 : atoi(argv[1]);
	for (int i = 0; i < 2; i++) {
		if (mode >= 0 && mode != i) continue;
		Code c(i == 0);
		void (*f)() = c.getCode<void (*)()>();
		Xbyak::util::Clock clk;
		clk.begin();
		f();
		clk.end();
		printf("%.2fclk\n", clk.getClock() / double(N));
	}
}