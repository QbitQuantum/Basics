LPCTSTR CInputDeviceList::GetHash()
{
	COcsCrypto	myHash;
	CInputDevice myObject;
	POSITION	pos;
	BOOL		bContinue;
	CString		csToHash;

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
		csToHash.Format( _T( "%s%s%s%s%s%s"), myObject.GetType(), myObject.GetManufacturer(),
						 myObject.GetCaption(), myObject.GetDescription(), myObject.GetPointingInterface(),
						 myObject.GetPointingType());
		myHash.HashUpdate( csToHash);
		bContinue = (pos != NULL);
		if (bContinue)
			myObject = GetNext( pos);
	}
	return myHash.HashFinal();
}