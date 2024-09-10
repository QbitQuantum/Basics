EXPORT_C TInt TMetaVarLenBase::Load(TPtrC8& aBuffer)
/**
 * Loads content of descriptor data member
 */
	{
	// Check if the descriptor is long enough
	TInt errlen = CheckBuf( aBuffer );
	if (errlen < 0)
		{
		return errlen;
		}

	//and copy whatever we can into the client descriptor
	CopyBuf(aBuffer,errlen);

	aBuffer.Set(aBuffer.Ptr() + errlen, aBuffer.Length() - errlen); //update pointer
	return KErrNone;
	}