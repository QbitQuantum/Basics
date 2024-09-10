// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
//
TInt CPolicyClientRequestHandler::RemovePolicyInfo(RPointerArray<CActionPolicy>& aPolInfo, TUint aAction, TBool aDelete)
	{
	CActionPolicy* tPol = NULL;
	TInt polInfoCount = aPolInfo.Count();
	
	for(TInt i = 0; i < polInfoCount; i++)
		{
		tPol = aPolInfo[i];
		if(tPol->iAction == aAction)
			{
			if(aDelete)
				{
				delete tPol;
				tPol = NULL;
				}
			aPolInfo.Remove(i);
			return KErrNone;
			}
		}
	return KErrNotFound;
	}