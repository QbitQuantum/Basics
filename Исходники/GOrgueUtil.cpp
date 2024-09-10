bool parseCDouble(double& result, wxString value)
{
	bool sign = false;
	unsigned pos;
	double shift = 0.1;
	result = 0;
	if (value.length() > 0 && value[0] == wxT('-'))
	{
		sign = true;
		value = value.Mid(1);
	}
	if (value.length() < 1)
		return false;
	for (pos = 0; pos < value.length(); pos++)
	{
		if (value[pos] == wxT('.'))
		{
			if (pos == 0)
				return false;
			pos++;
			break;
		}
		if (value[pos] < wxT('0') || wxT('9') < value[pos])
			return false;
		result = result * 10 + (value[pos] - wxT('0'));
	}
	for (; pos < value.length(); pos++)
	{
		if (value[pos] < wxT('0') || wxT('9') < value[pos])
			return false;
		result = result  + shift * (value[pos] - wxT('0'));
		shift = shift / 10;
	}
	if (sign)
		result = -result;
	return true;
}