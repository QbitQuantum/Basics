bool KConsoleDriver::flushAttributes(int fromX,int fromY,int toX,int toY,const CharAttribute *attributes)
{
#ifdef USE_M_API
	coord top = { (SHORT)fromX, (SHORT)fromY };
	dword result;
	if (!WriteConsoleOutputAttribute(hStdOut, attributes, toX * toY, top, &result))
	{
		return false;
	}
#endif
	return true;
}