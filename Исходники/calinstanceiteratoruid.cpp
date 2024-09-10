/** Uid instance iterator ConstructL

Fetches all the related entries to the UID and sets the currently indexed time

@internalComponent
*/
void CCalInstanceIteratorUid::ConstructL(const TDesC8& aUid, const TCalTime& aInstanceTime, TCalCollectionId aCollectionId)
	{
	// record the time to use for undated todos
	TTime now;
	now.HomeTime();
	iUndatedTodoTime.SetTimeLocalL(now);
	
	// Fetch all the entries that relate to the instance
	RPointerArray<CAgnSimpleEntry> simpleEntries;
	TCleanSimpleEntryArray cleanSimpleEntryArray(simpleEntries, iInstanceViewImpl.GetServ());
	CleanupStack::PushL(TCleanupItem(CCalInstanceViewImpl::DestroySimpleEntryArray, &cleanSimpleEntryArray));
	RArray<TInt> fileIds;
	iInstanceViewImpl.GetShortFileIdLC(fileIds);//It is in order 
	iInstanceViewImpl.GetServ().FetchSimpleEntriesByGuidL(aUid, simpleEntries, fileIds);
	CleanupStack::PopAndDestroy(&fileIds);
	
	const TInt KEntryCount(simpleEntries.Count());
	
	// There must be entries associated with this UID
	__ASSERT_ALWAYS(KEntryCount != 0, User::Leave(KErrNotFound));
	
	TBool instanceExists(EFalse);
	
	for (TInt i(0) ; i < KEntryCount ; ++i)
		{
		CCalLiteEntry* liteEntry = CCalLiteEntry::NewL(*simpleEntries[0], iInstanceViewImpl.GetServ());
		liteEntry->IncrementRefCount();
		simpleEntries.Remove(0);
		TInt appendError = iCalLiteEntries.Append(liteEntry);	
		if (appendError != KErrNone)
			{
			liteEntry->DecrementRefCount();
			User::Leave(appendError);
			}
		
		if (iInstanceViewImpl.IsValidInstanceL(liteEntry->LiteEntry(), aInstanceTime))
			{//Add the index of the entry which has the same time as aInstanceTime into iEntryWithSameTime
			if(liteEntry->LiteEntry().CollectionId() == aCollectionId)
				{
				instanceExists = ETrue;
				iCurrentIndexTime = aInstanceTime;
				iCurrentIndex = iEntryWithSameTime.Count();
				}
			iEntryWithSameTime.AppendL(i);
			}
		}
	
	__ASSERT_ALWAYS(instanceExists, User::Leave(KErrNotFound));
	CleanupStack::PopAndDestroy(); // simpleEntries
	}