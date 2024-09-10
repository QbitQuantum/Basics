	//--------------------------------------------------------------------------
	// Возвращает длину числа, переведенного в строку.
	size_t LengthOfLong(const __int64 digit)
	{
		char buffer[65];
		if (_i64toa_s(digit, buffer, 65, 10) == 0)
			return strnlen(buffer, _countof(buffer));
		else
			return 0;
	}