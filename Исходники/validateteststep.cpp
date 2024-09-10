void CValidateCertChainStep::CheckWarningsPresentAndRemoveL(const RArray<TValidationStatus>& aWarningsToCheckFor, RArray<TValidationStatus>& aWarningsToCheckIn)
	{
	TBool found;
	for (TInt warnings_index=0; warnings_index < aWarningsToCheckFor.Count(); ++warnings_index)
		{
		found = EFalse;
		for (TInt k=0; k < aWarningsToCheckIn.Count(); ++k)
			{
			if (ValidationStatusEqual(aWarningsToCheckFor[warnings_index], aWarningsToCheckIn[k]))
				{
				found = ETrue;
				aWarningsToCheckIn.Remove(k);
				break;
				}
			}
				
		if (!found)	
			{	
			ERR_PRINTF2(_L("ERROR: Warning not present: %d"), aWarningsToCheckFor[warnings_index].iReason);
			User::Leave(KErrGeneral); 
			}
		}	
	}