static std::string IntToStr (unsigned __int64 value)
{
	char buffer[100] = { 0 };
	_ui64toa_s (value, buffer, 100, 10);

	std::string result = buffer;
	for (size_t i = 3; i < result.length(); i += 4)
		result.insert (result.length() - i, 1, ',');

	return result;
};