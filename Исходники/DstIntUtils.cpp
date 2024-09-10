TCalLocalUid CDstIntUtils::ImportVCalL(RFs& aFs, CCalSession& aSession, CCalEntryView& aEntryView, const TDesC& aFileName)
	{
	RFileReadStream readStream;
	User::LeaveIfError(readStream.Open(aFs, aFileName, EFileRead));
	CleanupClosePushL(readStream);

	// Create ptr array for new entries
	RPointerArray<CCalEntry> entryArray;
	CleanupStack::PushL(TCleanupItem(ResetAndDestroyArrayOfEntries, &entryArray));

	CCalDataExchange* dataExchange = CCalDataExchange::NewL(aSession);
	CleanupStack::PushL(dataExchange);
	dataExchange->ImportL(KUidVCalendar, readStream, entryArray);

	TInt elements = entryArray.Count();
	TCalLocalUid id = 0;

	if(elements > 0)
		{
		CCalEntry* entry = entryArray[0];
		// add the first entry only
		while (entryArray.Count() > 1)
			{
			delete entryArray[1];
			entryArray.Remove(1);
			}
		TInt success = 0;
		aEntryView.StoreL(entryArray, success);
		id = entryArray[0]->LocalUidL();
		}

	CleanupStack::PopAndDestroy(dataExchange);
	CleanupStack::PopAndDestroy();	// ResetAndDestroyArrayOfEntries(entryArray)
	CleanupStack::PopAndDestroy();	// readStream.Close()

	return id;
	}