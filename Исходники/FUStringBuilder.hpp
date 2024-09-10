void FloatToString(FloatType f, Char* sz)
{
	Char* buffer = sz + 1;
	static const int digitCount = 6;
	int decimal, sign;

	// ecvt rounds the string for us: http://www.datafocus.com/docs/man3/ecvt.3.asp
	char* end = ecvt(f, digitCount, &decimal, &sign);

	if (sign != 0) (*buffer++) = '-';
	int count = digitCount;
	if (decimal > digitCount)
	{
		// We use the scientific notation: P.MeX
		(*buffer++) = (*end++); // P is one character.
		(*buffer++) = '.';

		// Mantissa (cleaned for zeroes)
		for (--count; count > 0; --count) if (end[count - 1] != '0') break;
		for (int i = 0; i < count; ++i) (*buffer++) = (*end++);
		if (buffer[-1] == '.') --buffer;

		// Exponent
		(*buffer++) = 'e';
		uint32 exponent = decimal - 1; // X
		if (exponent >= 10) (*buffer++) = (Char) ('0' + (exponent / 10));
		(*buffer++) = (Char) ('0' + (exponent % 10));
		(*buffer) = 0;
		return;
	}
	else if (decimal > 0)
	{
		// Simple number: A.B
		for (int i = 0; i < decimal; ++i) (*buffer++) = (*end++);
		if (decimal < digitCount) (*buffer++) = '.';
		count = digitCount - decimal;
	}
	else if (decimal < -digitCount)
	{
		// What case is this?
		decimal = count = 0;
	}
	else if (decimal < 0 || (decimal == 0 && *end != '0'))
	{
		// Tiny number: 0.Me-X
		(*buffer++) = '0'; (*buffer++) = '.';
		for (int i = 0; i < -decimal; ++i) (*buffer++) = '0';
		count = digitCount + decimal;
	}
	for (; count > 0; --count) if (end[count - 1] != '0') break;
	for (int i = 0; i < count; ++i) (*buffer++) = (*end++);
	if (decimal == 0 && count == 0) (*buffer++) = '0';
	if (buffer[-1] == '.') --buffer;
	(*buffer) = 0;
}