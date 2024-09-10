	std::string julian_short_month_name(unsigned month) {
		auto s = julian_month_name(month).substr(0, 3);
		s[1] = (char)toupper(s[1]);
		s[2] = (char)toupper(s[2]);
		return s;
	}