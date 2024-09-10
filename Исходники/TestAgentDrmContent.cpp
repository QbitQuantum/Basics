TInt CTestAgentDrmContent::ReadTUintvarL(TDes8& aBuffer, TInt Offset, TInt& aNumBytes) const
	{
	TUint8 byte;
	TInt Value=0;
	TBool Continue = ETrue;

	for(aNumBytes = 0; Continue ; aNumBytes++)
		{
		Value <<= 7;
		if(Offset + aNumBytes == aBuffer.Length())
			User::Leave(KErrOverflow);

		byte = aBuffer[Offset + aNumBytes];
		if((byte & 0x80) == 0)
			{
			Continue=EFalse;
			}
		else 
			{
			byte &= 0x7F;
			}

		Value+=byte;
		}
	return Value;
	}