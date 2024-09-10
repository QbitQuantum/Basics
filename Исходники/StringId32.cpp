	const char* StringId32::toString(char* buf)
	{
		snPrintf(buf, STRING_LENGTH, "%.8x", id);
		return buf;
	}