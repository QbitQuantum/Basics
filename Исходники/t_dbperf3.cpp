//Delete "aFullName" file.
static void DeleteFile(const TDesC& aFullName)
	{
	RFs fsSession;
	TInt err = fsSession.Connect();
	if(err == KErrNone)
		{
		TEntry entry;
		if(fsSession.Entry(aFullName, entry) == KErrNone)
			{
			err = fsSession.SetAtt(aFullName, 0, KEntryAttReadOnly);
			if(err != KErrNone) 
				{
				TheTest.Printf(_L("Error %d changing \"%S\" file attributes.\n"), err, &aFullName);
				}
			err = fsSession.Delete(aFullName);
			if(err != KErrNone) 
				{
				TheTest.Printf(_L("Error %d deleting \"%S\" file.\n"), err, &aFullName);
				}
			}
		fsSession.Close();
		}
	else
		{
		TheTest.Printf(_L("Error %d connecting file session. File: %S.\n"), err, &aFullName);
		}
	}