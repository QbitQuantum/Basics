void CzString::ToLower()
{
	char* pData = Data;
	for (int t = 0; t < Length; t++)
	{
		char c = *pData;
		if (IsUpper(c))
		{
			c += 'a' - 'A';
			*pData++ = c;
		}
		else
			pData++;
	}
}