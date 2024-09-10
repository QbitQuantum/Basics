void CGlxMediaListsTestCollectionPlugin::RemoveItemL(const TGlxMediaId& aId, RPointerArray<CItem>& aDatabase)
	{
	TIdentityRelation<CItem> match(&MatchById);
	CItem* mediaToCompare = new (ELeave) CItem();
	CleanupStack::PushL(mediaToCompare);
	mediaToCompare->iId = TGlxMediaId(aId);
	TInt index = aDatabase.Find(mediaToCompare, match);
	delete aDatabase[index];
	aDatabase.Remove(index);
	CleanupStack::PopAndDestroy(mediaToCompare);
	}