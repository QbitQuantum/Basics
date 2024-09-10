	bool write_string(Slice<char>& buffer, StringView v)
	{
		if (buffer.size() < v.length()) return false;
		
		memcpy(buffer.ptr(), v.c_str(), v.length());
		buffer.trim_front(v.length());
		return true;
	}