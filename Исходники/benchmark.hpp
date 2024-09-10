Ret benchmark1(const std::basic_string<C>& str, const std::basic_string<C>& key, F f)
{
	const int N = 1;
	int val = 0;
	f.set(str, key);
	Xbyak::util::Clock clk;

	for (int i = 0; i < N; i++) {
		typename F::type p = f.begin();
		typename F::type end = f.end();
		for (;;) {
			clk.begin();
			typename F::type q = f.find(p);
			clk.end();

			if (q == end) break;
			val += (int)(q - p);
			p = q + 1;
		}
	}
 if (val == 0) val = (int)(str.size()) * N;
	Ret ret;
	ret.val = val;
	ret.clk = clk.getClock() / (double)val;
	return ret;
}