		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::value_type
		dft_element_gen_impl_1(
			InputIterator first, InputIterator last,
			typename std::iterator_traits<InputIterator>::value_type::value_type arg,
			typename std::iterator_traits<InputIterator>::difference_type k = 0,
			typename std::iterator_traits<InputIterator>::value_type value
				= typename std::iterator_traits<InputIterator>::value_type(),
			typename std::iterator_traits<InputIterator>::value_type::value_type theta
				= typename std::iterator_traits<InputIterator>::value_type::value_type()
			)
		{
			typedef typename std::iterator_traits<InputIterator>::value_type value_type;
			using sprout::cos;
			using sprout::sin;
			return first == last ? value
				: value + sprout::detail::dft_element_gen_impl_1(
					sprout::next(first), last,
					arg,
					k + 1,
					*first * value_type(cos(theta), sin(theta)),
					arg * (k + 1)
					)
				;
		}