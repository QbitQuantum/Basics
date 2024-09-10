// ----------------------------------------------------------------------------
// CSIPProfileSIMRecord::FindSIPSchema
// ----------------------------------------------------------------------------
//
TPtrC8 CSIPProfileSIMRecord::RemoveSIPSchemaL( const TDesC8& aValue )
    {
    __ASSERT_ALWAYS (aValue.Length() > 0, User::Leave(KErrArgument));

	_LIT8(KSIPAndColon, "sip:");
	_LIT8(KSIPSAndColon, "sips:");

	TPtrC8 schemeAndColon;
	TInt sipSchemePos = aValue.FindF(KSIPAndColon);
	if (sipSchemePos < 0)
		{
		TInt sipsSchemePos = aValue.FindF(KSIPSAndColon);
		if (sipsSchemePos != 0) 
            {
            User::Leave (KErrArgument);
            }
		schemeAndColon.Set(KSIPSAndColon);
		}
	else
		{
		if (sipSchemePos != 0) 
            {
            User::Leave (KErrArgument);
            }
		schemeAndColon.Set(KSIPAndColon);
		}
	TPtrC8 remainder(aValue.Mid(schemeAndColon.Length()));
	return remainder;
    }    