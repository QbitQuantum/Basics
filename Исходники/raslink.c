BOOL 
	WAN_CheckForContext (
		IN PKIP_NDIS_ADAPTER pAdapter,
		IN PCHAR pProtoContext
		)
{
	PLIST_ENTRY ListEntry;
	PKIP_RAS_LINK pRasLink;
	BOOLEAN fbResult = FALSE;

	DBGLOG(( LTrace, "Context: %.2X%.2X%.2X%.2X\n", 
				pProtoContext[0],
				pProtoContext[1],
				pProtoContext[2],
				pProtoContext[3]
				));

	KIP_LOCK_ADAPTER(pAdapter);
	for ( ListEntry = pAdapter->RasLinkList.Flink; 
		ListEntry != &pAdapter->RasLinkList;
		ListEntry = ListEntry->Flink)
	{
		pRasLink = CONTAINING_RECORD(ListEntry,KIP_RAS_LINK,Interface.Link);
		if ( (RtlCompareMemory(&pRasLink->Interface.CurrentMacAddress[2], pProtoContext, 4) == 4) ){
			fbResult = TRUE;
			break;
		}
	}

	KIP_UNLOCK_ADAPTER(pAdapter);

	return fbResult;
}