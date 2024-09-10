HBufC* CScriptFile::ReadFileLC(const TDesC& aScript) const
	{
	HBufC8* file = NULL;

	TRAPD(err, file = ReadFileL(aScript));

	if (err)
		{
		TParse fileOut;
		err = iTestUtils.ResolveFile(*iComponent, aScript, fileOut);

		if (err)
			{
			iTestUtils.Test().Printf(_L("Cannot read file %S. Error=%d"), &aScript, err);
			User::Leave(err);
			}

		file = ReadFileL(fileOut.FullName());
		}

	CleanupStack::PushL(file);

	HBufC* buf = HBufC::NewL(file->Length());
	buf->Des().Copy(*file);
	CleanupStack::PopAndDestroy(file);
	CleanupStack::PushL(buf);
	return buf;
	}