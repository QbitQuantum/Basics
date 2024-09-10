bool Word::TryParseInt(int* outInt) const
{
	int result = 0;

	if (_backing[0] > 57 || _backing[0] < 48)
	{
		*outInt = 0;
		return false;
	}
	result += _backing[_length - 1] - 48;

	for (int i = 1; i < _length; ++i)
	{
		if (_backing[i] > 57 || _backing[i] < 48)
		{
			*outInt = 0;
			return false;
		}

		result += (_backing[_length - 1 - i] - 48) * static_cast<int>(powl(10, i));
	}

	*outInt = result;
	return true;
}