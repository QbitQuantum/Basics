void bench()
{
	Xbyak::util::Clock clk;
	const size_t N = 1000;
	const size_t M = 1000;
	Vuint m("14615016373309029182036848327162830196559325429831461501636150163733090291820368483271628301965593254298314615016373309029182036848327162830196559325429831461501637330902918203684832716283019655932542983");
	ZmZ<>::setModulo(m);
//	const char *str = "123456789012342342342499924234242422333333333333333333333256789112345678901234234234242423424242233333333333333333333325678911234567890123423423424242342424223333333333333333333332567891";
	const char *str = "82434016654300679721217353503190038836571781811386228921167322412819029493182";
//	ZmZ<> a(str);
	Vuint a(str), b(a);
	for (size_t i = 0; i < N; i++) {
		clk.begin();
		for (size_t j = 0; j < M; j++) {
//			a *= a;
			Vuint::mul(b, a, a); // 4268clk
//			Vuint::mul1(b, a, 123456789); // 128clk
//			Vuint::add(b, a, a); // 113clk
//			local::PrimitiveFunction::add1(&b[0], &a[0], a.size(), 1234566);
//			local::PrimitiveFunction::mul1(&b[0], &a[0], a.size(), 1234566);
//			Vuint::sub(b, a, a); // 140clk
		}
		clk.end();
	}
	printf("clk=%.3fclk\n", clk.getClock() / double(clk.getCount()) / M);
}