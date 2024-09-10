char* IntToString(int i, int iBase)
{
	int iCount = IncrementLogToStringCount();

	IToA(i, gaszLogToStringScratchPad[iCount], iBase);
	return gaszLogToStringScratchPad[iCount];
}