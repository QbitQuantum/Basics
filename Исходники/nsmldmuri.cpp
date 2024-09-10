// ------------------------------------------------------------------------------------------------
// TPtrC8 NSmlDmURI::ParentURI(const TDesC8& aURI)
// returns parent uri, i.e. removes last uri segment
// ------------------------------------------------------------------------------------------------
TPtrC8 NSmlDmURI::ParentURI(const TDesC8& aURI)
	{
	TBool onlyOneSeg = ETrue;
	TInt i;
	for(i=aURI.Length()-1;i>=0;i--)
		{
		if(aURI[i]==KNSmlDMUriSeparator)
			{
			onlyOneSeg = EFalse;
			break;
			}
		}
	if(onlyOneSeg)
		{
		return KNSmlDmRootUri();
		}
	else
		{
		return aURI.Left(i);
		}
	}