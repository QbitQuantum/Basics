BOOLEAN	ReleaseNetCardsInfo()
{
	LIST_ENTRY		*pListEntry=NULL;
	NETCARDS_INFO		*pNI=NULL;

	if (!IsListEmpty(&g_NetCardsInfoHeader.Next))
	{
		pListEntry = ExInterlockedRemoveHeadList(&g_NetCardsInfoHeader.Next, &g_NetCardsInfoLock);
		// 		LockResource(&g_NetCardsInfoLock, TRUE);
		// 		pListEntry = RemoveHeadList(&g_NetCardsInfoHeader.Next);
		// 		UnlockResource(&g_NetCardsInfoLock);
		pNI	=	CONTAINING_RECORD(pListEntry, NETCARDS_INFO, Next);
		if (pNI==NULL)
		{
			kprintf("what the hell is going on\n");

		}
		RtlFreeAnsiString(&pNI->Name);
		kfree(pNI);
	}

	return TRUE;
}