/**
Convert data from the API's form (as we're given it by RemCon) the
bearer-specific form.
*/
TInt CCoreSerialConverter::InterfaceToBearer(TUid aInterfaceUid,
		TUint aOperationId,
		const TDesC8& aData,
		TRemConMessageType aMsgType,
		TDes8& aBearerData) const
	{
	TInt ret = KErrCorrupt;

	if ( aData.Length() <= 10 )
		{
		if ( aMsgType == ERemConCommand )
			{
			aBearerData.Format(_L8("0x%08x 0x%02x %S %S"), aInterfaceUid, aOperationId, &KCmdText(), &aData);
			// Pad it up in case aData was less than 4 characters.
			while ( aBearerData.Length() < KRemConSerialBearerMessageLength )
				{
				aBearerData.Append(_L8(" "));
				}
			ret = KErrNone;
			}
		else if ( aMsgType == ERemConResponse )
			{
			aBearerData.Format(_L8("0x%08x 0x%02x %S %S"), aInterfaceUid, aOperationId, &KRspText(), &aData);
			// Pad it up in case aData was less than 4 characters.
			while ( aBearerData.Length() < KRemConSerialBearerMessageLength )
				{
				aBearerData.Append(_L8(" "));
				}
			ret = KErrNone;
			}
		}

	return ret;
	}