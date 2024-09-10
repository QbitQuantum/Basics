BOOL AddKeyClipboard(HWND hwnd,void *PGPsc,void *PGPtls)
{
	PGPContextRef context;
	char *pInput;
	DWORD dwInputSize;
	UINT ClipboardFormat;
	MYSTATE *ms;
	PGPtlsContextRef tls;
	PGPError err;

	// Check for files copied into clipboard from explorer
	if(OpenClipboard(hwnd)) 
	{
		if(IsClipboardFormatAvailable(CF_HDROP))
		{
			FILELIST *ListHead;
			HDROP hDrop;

			hDrop=(HDROP)GetClipboardData(CF_HDROP);
			ListHead=HDropToFileList(hDrop);

			if(ListHead!=0)
			{
				CloseClipboard();

				return AddKeyFileList(hwnd,
					PGPsc,PGPtls,ListHead);
			}
		}
		CloseClipboard();
	}

	err=kPGPError_NoErr;

	context=(PGPContextRef)PGPsc;
	tls=(PGPtlsContextRef)PGPtls;

	if(IsPGPError(PGPclEvalExpired(hwnd, PGPCL_ALLEXPIRED)))
		return FALSE;

	pInput=RetrieveClipboardData(hwnd, &ClipboardFormat, 
			                     &dwInputSize);

	if(!pInput)
	{
		PGPscMessageBox (hwnd,IDS_PGPERROR,IDS_NOCLIPBOARDCONTENTS,
					MB_OK|MB_ICONSTOP);
	}
	else
	{
		if((ClipboardFormat != CF_TEXT)||(*pInput==0))
		{
			PGPscMessageBox (hwnd,IDS_PGPERROR,IDS_NOCLIPBOARDTEXT,
				MB_OK|MB_ICONSTOP);
		}
		else
		{
			ms=(MYSTATE *)malloc(sizeof(MYSTATE));

			if(ms)
			{
				memset(ms, 0x00, sizeof(MYSTATE) );

				ms->context=context;
				ms->tlsContext=tls;
				ms->pInput=pInput;
				ms->dwInputSize=dwInputSize;
				ms->Operation=MS_ADDKEYCLIPBOARD;

				if(OpenRings(hwnd,context,&(ms->KeySet)))
				{
					err=SCProgressDialog(hwnd,DoWorkThread,ms,
						  0,"Adding Keys from Clipboard...",
						  "","",IDR_PROGAVI);

// If no PGP data in clipboard, warn....
					if(!(ms->FoundPGPData))
						PGPscMessageBox (hwnd,IDS_PGPERROR,IDS_NOPGPKEYSINCLIPBOARD,
							MB_OK|MB_ICONEXCLAMATION);

					PGPFreeKeySet(ms->KeySet);
				}
				free(ms);
			}
		}
		memset(pInput,0x00,dwInputSize);
		free(pInput);
	}

	if(IsPGPError(err))
		return FALSE;

	return TRUE;
}