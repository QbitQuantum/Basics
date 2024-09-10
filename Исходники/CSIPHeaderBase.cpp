// -----------------------------------------------------------------------------
// CSIPHeaderBase::ToTextL
// -----------------------------------------------------------------------------
//
EXPORT_C HBufC8* CSIPHeaderBase::ToTextL() const
	{
	TPtrC8 fullname(Name().DesC());
    // Because SIP Codec's string table has entry "expires" before "Expires",
    // and entry "require" before "Require",
    // literal "Expires" and "Require" must be used here. 
    // Changing the order of string table entries would have caused a SC break.	
	if (Name() == SIPStrings::StringF(SipStrConsts::EExpiresHeader))
	    {
        fullname.Set(KExpiresHeaderNameDes);
	    }
	else if (Name() == SIPStrings::StringF(SipStrConsts::ERequireHeader))
	    {
	    fullname.Set(KRequireHeaderNameDes);
	    }
	else
	    {
	    }
	TUint headerLength = fullname.Length();
	headerLength += KColonAndSpace().Length();
	HBufC8* encodedHeaderValue = ToTextValueL();
	headerLength += encodedHeaderValue->Length();

	CleanupStack::PushL (encodedHeaderValue);

	HBufC8* encodedHeader = HBufC8::NewL(headerLength);
	TPtr8 encodedHeaderPtr = encodedHeader->Des(); 
	encodedHeaderPtr.Append(fullname);
	encodedHeaderPtr.Append(KColonAndSpace);
	encodedHeaderPtr.Append(*encodedHeaderValue);
	
	CleanupStack::PopAndDestroy(encodedHeaderValue);

	return encodedHeader;
	}