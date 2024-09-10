	static array<unsigned char>^ GetString(char const* str)
	{
		size_t len = strnlen_s(str, 512);
		array<unsigned char>^ result = gcnew array<unsigned char>(len);
		for (size_t i = 0u; i < len; ++i)
			result[i] = str[i];
		return result;
	}