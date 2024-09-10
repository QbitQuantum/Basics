//失败返回0
ULONG	GetTargetProtocolBlockWin7(char *ProName, DWORD dwLen)
{

	UNICODE_STRING	uniNPF;
	ULONG			uHeader=0;
	NTSTATUS		status = STATUS_SUCCESS;
	PNDIS_PROTOCOL_BLOCKWin7	pProtoBLock=NULL;
	BOOLEAN			bFound	=	FALSE;
	PNDIS_PROTOCOL_BLOCKWin7	pNpfProtocolBlock=NULL;
	char szBuffer[1024];
	ANSI_STRING	aniStr1;

	RtlZeroMemory(szBuffer, sizeof(szBuffer));

	if (dwLen>sizeof(szBuffer))
	{
		return STATUS_UNSUCCESSFUL;
	}

	RtlMoveMemory(szBuffer, ProName, dwLen);

	RtlInitAnsiString(&aniStr1, szBuffer);
	RtlAnsiStringToUnicodeString(&uniNPF, &aniStr1, TRUE);


	do 
	{

		uHeader	=	GetProtocolHeader();
		if (uHeader==0)
		{
			status	=	STATUS_UNSUCCESSFUL;
			break;
		}
		pProtoBLock	=	(PNDIS_PROTOCOL_BLOCKWin7)uHeader;
		while(pProtoBLock)
		{
			if (RtlEqualUnicodeString(&pProtoBLock->Name, &uniNPF,TRUE))
			{
				bFound	=	TRUE;
				break;
			}
			pProtoBLock	=	(PNDIS_PROTOCOL_BLOCKWin7)pProtoBLock->NextProtocol;
		}

		if (!bFound)
		{
			kprintf("Can not find  protocol name: %s\n", ProName);
			break;
		}
		pNpfProtocolBlock	=	pProtoBLock;

		//NdisDeregisterProtocol(&status, (NDIS_HANDLE)uHeader);	// deregister it

	} while (0);

	RtlFreeUnicodeString(&uniNPF);

	return (ULONG)pNpfProtocolBlock;

}