MprBuf::MprBuf(int initialSize, int max)
{
	buf = 0;
	refillProc = 0;
	refillArg = 0;
	setBuf(initialSize, max);
}