inline unsigned int BitCountNeededToEncode(unsigned int data)
{
#if defined(_X360)
	return (32 - CountLeadingZeros(data+1)) - 1;
#else
	unsigned long firstBit;
	_BitScanReverse(&firstBit,data+1);
	return firstBit;
#endif
}