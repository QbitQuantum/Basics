TInt RBTBaseband::Enumerate(RBTDevAddrArray& aBTDevAddrArray, TUint aMaxNumber)
	{
	if (!SubSessionHandle())
		{
		return KErrNotReady;
		}

	__ASSERT_DEBUG(aMaxNumber>=1, Panic(EBadArgument));
	if(!aMaxNumber)
		{
		return KErrArgument;
		}
	HBufC8* buffer=0;
	const TInt KAddrLen = sizeof(TBTDevAddr);

	TRAPD(err, buffer = HBufC8::NewL(aMaxNumber*KAddrLen));
	if(err)
		{
		return KErrNoMemory;
		}

	TPtr8 ptr = buffer->Des();
	err = iSocket.GetOpt(EBBEnumeratePhysicalLinks, KSolBtLMProxy, ptr);
	if (err)
		{
		delete buffer;
		return err;
		}

	/**
	Parse the supplied descriptor
	*/
	
	aBTDevAddrArray.Reset();
	while(ptr.Length()>=KBTDevAddrSize)
		{
		TBTDevAddr parsedAddr(ptr.Mid(ptr.Length()-KAddrLen, KBTDevAddrSize));
		ptr.SetLength(Max(ptr.Length()-KAddrLen, 0));
		aBTDevAddrArray.Append(parsedAddr);
		}

	delete buffer;
	return KErrNone;
	}