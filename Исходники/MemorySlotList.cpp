LPCTSTR CMemorySlotList::GetHash()
{
	COcsCrypto	myHash;
	CMemorySlot myObject;
	POSITION	pos;
	BOOL		bContinue;
	static CString		csToHash;

	if (GetCount() == 0)
		return NULL;
	if (!myHash.HashInit())
		return NULL;
	pos = GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myObject = GetNext( pos);
	while (bContinue)
	{
		csToHash.Format( _T( "%s%s%s%s%s%s%u%s"), myObject.GetCaption(), myObject.GetDescription(),
						 myObject.GetCapacity(), myObject.GetUsage(), myObject.GetType(),
						 myObject.GetSpeed(), myObject.GetSlotNumber(), myObject.GetSN());
		myHash.HashUpdate( csToHash);
		bContinue = (pos != NULL);
		if (bContinue)
			myObject = GetNext( pos);
	}
	return myHash.HashFinal();
}