//1. make a copy(A) of supported oids
//2. set supported oids to list from config
//3. reset supported oids
//4. get supported oids(B)
//5. iterate over B, find and remove first match in A.  if not found we error
//6. if A is not empty we error
void CPkixCertResetSupportedOidsStep::PerformTestL()
	{
	CPkixCertStepBase::PerformTestL();
	
	//1. make a copy(A) of supported oids
	const RPointerArray<TDesC>& suppOids = iCertChain->SupportedCriticalExtensions();	
	//CleanupClosePushL(suppOids);	//don't need to do this as a ref and done in stepbase destructor
	RPointerArray<HBufC> startSuppOids;
	CleanupResetAndDestroy<RPointerArray<HBufC> >::PushL(startSuppOids);
		
	HBufC* des;
	TInt i;
	for (i=0; i < suppOids.Count(); ++i)
		{
		des = (suppOids[i])->AllocLC();
		startSuppOids.AppendL(des);
		CleanupStack::Pop(des);
		}

	//2. set supported oids to list from config
	iCertChain->SetSupportedCriticalExtensionsL(iProcessedOids);
	//3. reset supported oids
	iCertChain->ResetSupportedCriticalExtsToDefaultL();
	//4. get supported oids(B)
	const RPointerArray<TDesC>& suppOids2 = iCertChain->SupportedCriticalExtensions();
	
	//5. iterate over B, find and remove first match in A.  if not found we error
	TBool found;
	for (i=0; i < suppOids2.Count(); ++i)
		{
		found = EFalse;
		for (TInt j=0; j < startSuppOids.Count(); ++j)
			{
			if ((*suppOids2[i]) == (*startSuppOids[j]))
				{
				found = ETrue;
				delete (startSuppOids[j]);
				startSuppOids.Remove(j);
				break;
				}
			}
		if (!found)	
			{
			ERR_PRINTF2(_L("ERROR: Extra OID found in result: %S"), suppOids2[i]);
			User::Leave(KErrGeneral);
			}
		}
		
	//6. if A is not empty we error
	if (startSuppOids.Count() != 0)
		{
		for (TInt j=0; j < startSuppOids.Count(); ++j)
			{	
			ERR_PRINTF2(_L("ERROR: OID missing from result: %S"), startSuppOids[j]);
			}
		User::Leave(KErrGeneral);
		}		
	
	CleanupStack::PopAndDestroy(2, iCertChain);	
	}