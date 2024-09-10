EXPORT_C HBufC8* CTestConfig::ReplaceLC(const TDesC8& aOld, const TDesC8& aNew, const TDesC8& aOldString)
	{
	HBufC8* rString = aOldString.AllocLC();
	TInt oldLen = aOld.Length();
	TInt newLen = aNew.Length();

	if (!oldLen)
		return rString;

	for (TInt pos = 0; pos < rString->Length(); pos += newLen)
		{
		TPtrC8 ptrC = rString->Mid(pos);
		TInt find = ptrC.Find(aOld);

		if (find == KErrNotFound)
			return rString;
	
		pos += find;

		if (newLen > oldLen)
			{
			rString = rString->ReAllocL(rString->Length() + newLen - oldLen);
			CleanupStack::Pop();
			CleanupStack::PushL(rString);
			}

		TPtr8 ptr(rString->Des());
		ptr.Replace(pos, oldLen, aNew);
		}

	return rString;
	}