// ---------------------------------------------------------------------
SInt32 WinMBCString::Find(const WinMBCString& other, SInt32 startIndex /* = 0 */) const
{
	const unsigned char* target = reinterpret_cast<const unsigned char*>(innerString.c_str() + startIndex);
	const unsigned char* found = _mbsstr(target, reinterpret_cast<const unsigned char*>(other.innerString.c_str()));
	if (NULL == found)
	{
		return -1;
	}
	else
	{
		return found - target + startIndex;
	}
}