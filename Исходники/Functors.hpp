	static typename Function::value_type derivative(
			const Function &f,
			const typename Function::value_type &x)
	{
		typedef typename Function::value_type   value_type;
		typedef typename ValueType<value_type>::value_type T;

		// Find minimum value for h
		const std::size_t digits = std::numeric_limits<T>::digits;
		const std::size_t bits   = CHAR_BIT * sizeof(std::size_t);
		const std::size_t N      = std::min(digits, bits-1);

		assert(1ul << N);

		typename Function::value_type x_min_h, x_plus_h, deriv;
		for (std::size_t i = 0; i < x.size(); ++i)
		{
			using std::abs;
			const T h = (x[i] != 0) ? abs(x[i]) / T(1ul << (1ul+N/2)) :
						T(1) / T(1ul << (1ul+N/2));
			assert(h > 0);
			x_min_h  = x; x_min_h[i]  -= h;
			x_plus_h = x; x_plus_h[i] += h;
			deriv[i] = (f(x_plus_h) - f(x_min_h)) / (h+h);
		}
		return deriv;
	}