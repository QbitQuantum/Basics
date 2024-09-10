// Largely based off of undelete.c from sysinternals
BOOLEAN GetUserSIDFromProcess(EPROCESS *pProcess, UNICODE_STRING *pusSID)
{
	NTSTATUS status;
	ULONG RetLen;
	HANDLE hToken;
	PTOKEN_USER tokenInfoBuffer;
	PACCESS_TOKEN Token;

	Token = PsReferencePrimaryToken(pProcess);

	status = ObOpenObjectByPointer(Token, 0, NULL, TOKEN_QUERY, NULL, KernelMode, &hToken);
	ObDereferenceObject(Token);

	if(!NT_SUCCESS(status))
		return FALSE;

	// Get the size of the sid.
	status = ZwQueryInformationToken(hToken, TokenUser, NULL, 0, &RetLen);
	if(status != STATUS_BUFFER_TOO_SMALL) {
    ZwClose(hToken);
    return FALSE;
  }

	tokenInfoBuffer = (PTOKEN_USER)ExAllocatePoolWithTag(NonPagedPool, RetLen, HELPER_POOL_TAG);
	if(tokenInfoBuffer)
      status = ZwQueryInformationToken(hToken, TokenUser, tokenInfoBuffer, RetLen, &RetLen);
 
  if(!NT_SUCCESS(status) || !tokenInfoBuffer ) {
    DBGOUT(("Error getting token information: %x\n", status));
    if(tokenInfoBuffer)
			ExFreePool(tokenInfoBuffer);
    ZwClose(hToken);
    return FALSE;
  }
  ZwClose(hToken);

  status = RtlConvertSidToUnicodeString(pusSID, tokenInfoBuffer->User.Sid, FALSE);
  ExFreePool(tokenInfoBuffer);

  if(!NT_SUCCESS(status)) {
    DBGOUT(("Unable to convert SID to UNICODE: %x\n", status ));
    return FALSE;
  }

	return TRUE;
}