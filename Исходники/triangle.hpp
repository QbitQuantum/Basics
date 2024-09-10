		inline SPROUT_CONSTEXPR T
		triangle_value_impl(T const& t) {
			typedef double elem_type;
			using sprout::sin;
			using sprout::asin;
			return T(sprout::math::two_div_pi<elem_type>()) * asin(sin(T(sprout::math::two_pi<elem_type>()) * t));
		}