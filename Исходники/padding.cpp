void CPaddingSSLv3::DoPadL(const TDesC8& aInput,TDes8& aOutput)
	{
	TInt paddingBytes=BlockSize()-(aInput.Length()%BlockSize());
	aOutput.Append(aInput);
	aOutput.SetLength(aOutput.Length()+paddingBytes);
	for (TInt i=1;i<=paddingBytes;i++)
		{
		aOutput[aOutput.Length()-i]=(TUint8)(paddingBytes-1);
		}
	}