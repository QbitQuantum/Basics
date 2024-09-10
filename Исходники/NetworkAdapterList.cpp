LPCTSTR CNetworkAdapterList::GetHash()
{
	COcsCrypto	myHash;
	CNetworkAdapter myObject;
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
		csToHash.Format( _T( "%s%s%s%s%s%s%s%s%s"), myObject.GetDescription(), myObject.GetType(),
						 myObject.GetTypeMIB(), myObject.GetMACAddress(),
						 myObject.GetOperationalStatus(), myObject.GetIPAddress(), myObject.GetIPNetMask(),
						 myObject.GetGateway(), myObject.GetDhcpServer());
		myHash.HashUpdate( csToHash);
		bContinue = (pos != NULL);
		if (bContinue)
			myObject = GetNext( pos);
	}
	return myHash.HashFinal();
}