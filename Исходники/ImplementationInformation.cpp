/**
Intended Usage	: Stream out the internal state to aStream.	

Error Condition	: Leave with the error code.
@leave  		KErrNoMemory.
@leave  		@see RWriteStream.
@since			7.0
@param			aClientSide a boolean indicating whether the streaming is to performed in client/server side
@param			aStream The stream to store the data in.
@pre 			CImplementationInformation is fully constructed and initialized
*/
void CImplementationInformation::ExternalizeL(TBool aClientSide,RWriteStream& aStream) const
	{
	aStream.WriteInt32L(iImplementationUid.iUid);
	aStream.WriteInt32L(iVersion);
	if(iDisplayName)
		{
		TPtr outputBuf = iDisplayName->Des();
		aStream.WriteInt32L(outputBuf.Length());
		aStream.WriteL(outputBuf);
		}
	else
		{
		aStream.WriteInt32L(0);
		}

	if(iData)
		{
		TPtr8 outputBuf = iData->Des();
		aStream.WriteInt32L(outputBuf.Length());
		aStream.WriteL(outputBuf);
		}
	else
		{
		aStream.WriteInt32L(0);
		}

	if(iOpaqueData)
		{
		TPtr8 outputBuf = iOpaqueData->Des();
		aStream.WriteInt32L(outputBuf.Length());
		aStream.WriteL(outputBuf);
		}
	else
		{
		aStream.WriteInt32L(0);
		}
	if (aClientSide)
		{
		aStream.WriteInt32L(iDrive);		
		aStream.WriteInt32L(iVid.iId);		
		}
	TInt additionalImplInfo=iRomOnly;
	additionalImplInfo|=iRomBased<<1;
	additionalImplInfo|=iDisabled<<2;
	aStream.WriteInt8L(additionalImplInfo);
	
	if (iExtendedInterfaceList != NULL)
		{
		TInt count = iExtendedInterfaceList->Count();
		aStream.WriteInt32L(count);
		for(TInt i = 0; i < count; ++i)
			{
	   		aStream.WriteInt32L((*iExtendedInterfaceList)[i].iUid);
			}
		}
	else
		{
		aStream.WriteInt32L(KNoneExtendedInterface);
		}
	}