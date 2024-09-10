	void str_replaceAll(UString& input, const UString& from, const UString& to)
	{
		size_t pos = 0;
		while ((pos = input.find(from, pos)) != UString::npos) {
			input.replace(pos, from.length(), to);
			pos += to.length();
		}
	}