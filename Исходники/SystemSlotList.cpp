LPCTSTR CSystemSlotList::GetHash()
{
    COcsCrypto	myHash;
    CSystemSlot myObject;
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
        csToHash.Format( _T( "%s%s%s%s%s"), myObject.GetName(), myObject.GetDescription(),
                         myObject.GetSlotDesignation(), myObject.GetUsage(), myObject.GetStatus());
        myHash.HashUpdate( csToHash);
        bContinue = (pos != NULL);
        if (bContinue)
            myObject = GetNext( pos);
    }
    return myHash.HashFinal();
}