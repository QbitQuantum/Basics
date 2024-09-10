inline static void XLogRecPtr_Zero(XLogRecPtr *xlogLoc)
{
	MemSet(xlogLoc, 0, sizeof(XLogRecPtr));
}