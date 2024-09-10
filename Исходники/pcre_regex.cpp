		void swap(data &other)
		{
			expression.swap(other.expression);
			std::swap(flags,	other.flags);
			std::swap(re,		other.re);
			std::swap(are,		other.are);
			std::swap(re_size,	other.re_size);
			std::swap(are_size,	other.are_size);
			std::swap(match_size,	other.match_size);
		}