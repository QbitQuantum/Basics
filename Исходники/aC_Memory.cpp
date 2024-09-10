DWORD Mem2Hash(BYTE *mem, int length)
{
	DWORD dwHash;
	dwHash = 0;
	do
	{
		dwHash = _rotr((DWORD)dwHash, 13);
		dwHash += *mem++;
	} while (--length);
	return dwHash;
}