		inline SPROUT_CONSTEXPR T
		sinusoid_value(T const& amplitude, T const& phase, T const& d, Index i) {
			using sprout::sin;
			return amplitude * sin(d * T(i) + phase);
		}