void COptionNode::Dump(const TDesC& aTag, const TDesC& aFile)
	{
	RFileLogger f;
	if (f.Connect() == KErrNone)
		{
		f.CreateLog(aTag, aFile, EFileLoggingModeAppend);
		TInt i = 0;
		while (KOptions[i].iCode != OpCode() && ++i < KNumberOfSupportedOptions){/*do nothing*/}
		
		TInt n = iPtr8[1];
		if (i < KNumberOfSupportedOptions)
			{
			f.WriteFormat(_L8("Option Code: %s, length: %d"), KOptions[i].iName, n);
			}
		else
			{
			f.WriteFormat(_L( "Option Code: %d, length %d" ), OpCode(), n );
			}
		if (GetItemLength() > 2)
			{
			f.HexDump(NULL, NULL, GetBodyPtr(), GetLength());
			}
		f.CloseLog();
		f.Close();
		}
	}