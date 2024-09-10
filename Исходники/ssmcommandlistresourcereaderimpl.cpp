void CSsmCommandListResourceReaderImpl::CResourcePool::GetCommandListIdsL(RArray<TInt>& aArray) const
	{
	TInt count = iMappings.Count();
	__ASSERT_ALWAYS(count > 0, PanicNow(KPanicCmdResourceReader, ENotInitialized3));
	if (aArray.Count() != 0)
		{
		SSMLOGLEAVE(KErrArgument);
		}
	aArray.ReserveL(count);
#ifdef SYMBIAN_SSM_FLEXIBLE_MERGE
	TInt i = 0;
	for(i = 0; i < iMappings.Count() - 1 ; ++i)
		{
		if(iMappings[i].iCommandListId != iMappings[i+1].iCommandListId)
			{
			aArray.AppendL(iMappings[i].iCommandListId);
			}
		}
	//append the last element anyway as it is already compared
	aArray.AppendL(iMappings[i].iCommandListId);
	aArray.Compress();
		
	DEBUGPRINT2(_L("The number of substates in resource files : %d"),iMappings.Count() );
	DEBUGPRINT2(_L("The number of substates after filtering duplicates : %d"),aArray.Count());
#else
	for(TInt i = 0; i < count; ++i)
		{
		aArray.AppendL(iMappings[i].iCommandListId);
		}
#endif
	}