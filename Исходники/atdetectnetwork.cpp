// ---------------------------------------------------------------------------
// NetworkIdL
// Utility function to translate the 5 digit ASCII network identification 
// returned by the ME into Mobile Country Code (aCountryCode) and a Mobile 
// Network Code (aNetworkIdentity) strings. Tbe format returned by the ME is 
// XXXYY, where XXX represents the Mobile Country Code and YY represents the 
// Mobile Network Code.
// ---------------------------------------------------------------------------
static TInt NetworkIdL(const TDesC8& aCode,
					   RMobilePhone::TMobilePhoneNetworkCountryCode& aCountryCode, 
					   RMobilePhone::TMobilePhoneNetworkIdentity& aNetworkIdentity)
	{
	if (aCode.Length()!=5)
		{
		return KErrGeneral;
		}
	
	aCountryCode.SetLength(3);
	aCountryCode[0] = aCode[0];
	aCountryCode[1] = aCode[1];
	aCountryCode[2] = aCode[2];

	aNetworkIdentity.SetLength(2);
	aNetworkIdentity[0] = aCode[3];
	aNetworkIdentity[1] = aCode[4];
	return KErrNone;
	}