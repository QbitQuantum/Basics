	const char* StringId64::toString(char* buf)
	{
		snPrintf(buf, STRING_LENGTH, "%.16" PRIx64, id);
		return buf;
	}