storage_number pack_storage_number(calculated_number value, uint32_t flags)
{
	// bit 32 = sign 0:positive, 1:negative
	// bit 31 = 0:divide, 1:multiply
	// bit 30, 29, 28 = (multiplier or divider) 0-6 (7 total)
	// bit 27, 26, 25 flags
	// bit 24 to bit 1 = the value

	storage_number r = get_storage_number_flags(flags);
	if(!value) return r;

	int m = 0;
	calculated_number n = value;

	// if the value is negative
	// add the sign bit and make it positive
	if(n < 0) {
		r += (1 << 31); // the sign bit 32
		n = -n;
	}

	// make its integer part fit in 0x00ffffff
	// by dividing it by 10 up to 7 times
	// and increasing the multiplier
	while(m < 7 && n > (calculated_number)0x00ffffff) {
		n /= 10;
		m++;
	}

	if(m) {
		// the value was too big and we divided it
		// so we add a multiplier to unpack it
		r += (1 << 30) + (m << 27); // the multiplier m

		if(n > (calculated_number)0x00ffffff) {
			error("Number " CALCULATED_NUMBER_FORMAT " is too big.", value);
			r += 0x00ffffff;
			return r;
		}
	}
	else {
		// 0x0019999e is the number that can be multiplied
		// by 10 to give 0x00ffffff
		// while the value is below 0x0019999e we can
		// multiply it by 10, up to 7 times, increasing
		// the multiplier
		while(m < 7 && n < (calculated_number)0x0019999e) {
			n *= 10;
			m++;
		}

		// the value was small enough and we multiplied it
		// so we add a divider to unpack it
		r += (0 << 30) + (m << 27); // the divider m
	}

#ifdef STORAGE_WITH_MATH
	// without this there are rounding problems
	// example: 0.9 becomes 0.89
	r += lrint((double) n);
#else
	r += (storage_number)n;
#endif

	return r;
}