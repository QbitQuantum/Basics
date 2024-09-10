	RationalNumber operator ^ (const RationalNumber& B) const throw(std::invalid_argument)
	{
		if (!isFraction() || !B.isInteger())
		{
			return RationalNumber(powl(getRealNumber(), B.getRealNumber()));
		}
		RationalNumber S(1, 1);
		RationalNumber A = *this;
		long long n = B.numerator;
		if (n < 0)
		{
			A = RationalNumber(1, 1) / A;
			n = -n;
		}
		while (n)
		{
			if (n & 1)
			{
				S = S * A;
			}
			A = A * A;
			n >>= 1;
		}
		return S;
	}