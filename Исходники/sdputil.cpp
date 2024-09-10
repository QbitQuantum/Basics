// -----------------------------------------------------------------------------
// SdpUtil::IsTokenTextPair
// Checks if aValue is valid pair ("valid token":"valid byte-string")
// -----------------------------------------------------------------------------
//
TBool SdpUtil::IsTokenTextPair(
    const TDesC8& aValue, 
    TInt aStart,
    TInt aEnd )
	{
	// token ":" text
	TBool result = EFalse;
	if ( aStart >= 0 && aEnd <= aValue.Length() && aStart < aEnd )
		{
		TPtrC8 subVal = aValue.Mid( aStart, aEnd - aStart );
		TInt colonPos = subVal.Locate( KColonChar );
		result = colonPos != KErrNone &&
                 IsToken( subVal, 0, colonPos ) &&
                 IsByteString( subVal, colonPos + 1, subVal.Length() );
		}
	return result;
	}