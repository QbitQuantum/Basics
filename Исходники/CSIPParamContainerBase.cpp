// -----------------------------------------------------------------------------
// CSIPParamContainerBase::ToTextLC
// -----------------------------------------------------------------------------
//
HBufC8* CSIPParamContainerBase::ToTextLC () const
	{
	TUint encodedLength = 0;

	RPointerArray<HBufC8> paramsAsText;
	CleanupStack::PushL (TCleanupItem(ResetAndDestroy,&paramsAsText));

	for (TInt i=0; i < iParams.Count(); i++)
		{
		HBufC8* paramAsText = iParams[i]->ToTextLC();
		encodedLength += paramAsText->Length();
		if (i < iParams.Count()-1) 
		    {
		    encodedLength += 1; // param separator
		    }
		paramsAsText.AppendL(paramAsText);
		CleanupStack::Pop(paramAsText);
		}
	
	HBufC8* encodedParams = HBufC8::NewL (encodedLength);
	TPtr8 encodedParamsPtr = encodedParams->Des();

	for (TInt j=0; j < paramsAsText.Count(); j++)
		{
		encodedParamsPtr.Append (*paramsAsText[j]);
		if (j < paramsAsText.Count()-1)
			{
			encodedParamsPtr.Append(iParamSeparator);
			}
		}

	CleanupStack::PopAndDestroy(1); // paramsAsText
	CleanupStack::PushL(encodedParams);
	return encodedParams;
	}