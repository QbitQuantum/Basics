// buf to array
EXPORT_C TInt CRpsMsg::InternalizeL(const TDesC8& aBufIn)
	{
	TInt length(aBufIn.Length());
	if(length <= 0)
		{
		return KErrCorrupt;
		}
		
	if(iMsgDataArray != NULL)
		iMsgDataArray->Reset();
	
	TBuf8<KMaxElementSize> buf;
	
	// Dismantle msg into data elements first 
	TBool stop(EFalse);
	while (stop == EFalse)
		{
		TPtrC8 ptr = aBufIn.Right(length);
		
		TInt offset = ptr.Find(KComma);
		
		if(offset == KErrNotFound)
			{
			if(length > 0)
				{
				buf.Copy(ptr);
				iMsgDataArray->AppendL(buf);
				break;
				}	
			}

		buf.Copy(ptr.Left(offset));
		iMsgDataArray->AppendL(buf);
		length -= ++offset;
		if(length <= 0)
			{
			stop = ETrue;
			}
		}
	
	return KErrNone;
	}