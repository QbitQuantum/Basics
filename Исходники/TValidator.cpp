/**
	Checks whether valid parameter names and values exist in the 
	whole path of the tel-uri.
								
	@param		aName	The descriptor for parameter name to be checked as per RFC3966.
	@param		aValue	The descriptor for value to be checked as per RFC3966.
	@return		A boolean value of ETrue if uri contains valid parameters and values,
				EFalse if it does not.
 */
TBool TValidatorTel::IsValidParamSegment(const TDesC8& aName, const TDesC8& aValue) const
	{
	//Validation of the Name
	if (!aName.Length() || !IsValidCharacters(aName, KCharSetParamAll) )
		{
		return EFalse;	
		}
	//Validation of the Value based on ISDN, EXTN, Phone-context or any.
	if( ( KIsdnSubAddress().CompareF(aName) == 0 && !IsValidCharacters(aValue, KCharSetParamAll, ETrue) ) ||
		( KExtension().CompareF(aName) == 0 && !IsValidCharacters(aValue, KCharSetNumber) ) ||
		( KContext().CompareF(aName) == 0 && !IsValidCharacters(aValue, KCharSetParamAll) ) ||
		( KIsdnSubAddress().CompareF(aName) != 0 && 
		KExtension().CompareF(aName) != 0	&&
		KContext().CompareF(aName) != 0 &&
		!IsValidCharacters(aValue, KCharSetParamAll, ETrue) ) )
		{
		return EFalse;	
		}
	return ETrue;
	}