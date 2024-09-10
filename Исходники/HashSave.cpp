VOID __fastcall HashSaveWorkerMain( PHASHSAVECONTEXT phsctx )
{
	// Note that ALL message communication to and from the main window MUST
	// be asynchronous, or else there may be a deadlock.

	// Prep: expand directories, max path, etc. (prefix was set by earlier call)
	PostMessage(phsctx->hWnd, HM_WORKERTHREAD_TOGGLEPREP, (WPARAM)phsctx, TRUE);
	if (! HashCalcPrepare(phsctx))
        return;
    HashCalcSetSaveFormat(phsctx);
	PostMessage(phsctx->hWnd, HM_WORKERTHREAD_TOGGLEPREP, (WPARAM)phsctx, FALSE);

    // Extract the slist into a vector for parallel_for_each
    std::vector<PHASHSAVEITEM> vecpItems;
    vecpItems.resize(phsctx->cTotal + 1);
    SLBuildIndex(phsctx->hList, (PVOID*)vecpItems.data());
    assert(vecpItems.back() == nullptr);
    vecpItems.pop_back();
    assert(vecpItems.back() != nullptr);

#ifdef USE_PPL
    const bool bMultithreaded = vecpItems.size() > 1 && IsSSD(vecpItems[0]->szPath);
    concurrency::concurrent_vector<void*> vecBuffers;  // a vector of all allocated read buffers (one per thread)
    DWORD dwBufferTlsIndex = TlsAlloc();               // TLS index of the current thread's read buffer
    if (dwBufferTlsIndex == TLS_OUT_OF_INDEXES)
        return;
#else
    constexpr bool bMultithreaded = false;
#endif

    PBYTE pbTheBuffer;  // file read buffer, used iff not multithreaded
    if (! bMultithreaded)
    {
        pbTheBuffer = (PBYTE)VirtualAlloc(NULL, READ_BUFFER_SIZE, MEM_COMMIT, PAGE_READWRITE);
        if (pbTheBuffer == NULL)
            return;
    }

    // Initialize the progress bar update synchronization vars
    CRITICAL_SECTION updateCritSec;
    volatile ULONGLONG cbCurrentMaxSize = 0;
    if (bMultithreaded)
        InitializeCriticalSection(&updateCritSec);

#ifdef _TIMED
    DWORD dwStarted;
    dwStarted = GetTickCount();
#endif

    class CanceledException {};

    // concurrency::parallel_for_each(vecpItems.cbegin(), vecpItems.cend(), ...
    auto per_file_worker = [&](PHASHSAVEITEM pItem)
	{
        WHCTXEX whctx;

        // Indicate which hash type we are after, see WHEX... values in WinHash.h
        whctx.dwFlags = 1 << (phsctx->ofn.nFilterIndex - 1);

        PBYTE pbBuffer;
#ifdef USE_PPL
        if (bMultithreaded)
        {
            // Allocate or retrieve the already-allocated read buffer for the current thread
            pbBuffer = (PBYTE)TlsGetValue(dwBufferTlsIndex);
            if (pbBuffer == NULL)
            {
                pbBuffer = (PBYTE)VirtualAlloc(NULL, READ_BUFFER_SIZE, MEM_COMMIT, PAGE_READWRITE);
                if (pbBuffer == NULL)
                    throw CanceledException();
                // Cache the read buffer for the current thread
                vecBuffers.push_back(pbBuffer);
                TlsSetValue(dwBufferTlsIndex, pbBuffer);
            }
        }
#endif

#pragma warning(push)
#pragma warning(disable: 4700 4703)  // potentially uninitialized local pointer variable 'pbBuffer' used
		// Get the hash
		WorkerThreadHashFile(
			(PCOMMONCONTEXT)phsctx,
			pItem->szPath,
			&whctx,
			&pItem->results,
            bMultithreaded ? pbBuffer : pbTheBuffer,
			NULL, 0,
            bMultithreaded ? &updateCritSec : NULL, &cbCurrentMaxSize
#ifdef _TIMED
          , &pItem->dwElapsed
#endif
        );

        if (phsctx->status == PAUSED)
            WaitForSingleObject(phsctx->hUnpauseEvent, INFINITE);
		if (phsctx->status == CANCEL_REQUESTED)
            throw CanceledException();

		// Write the data
		HashCalcWriteResult(phsctx, pItem);

		// Update the UI
		InterlockedIncrement(&phsctx->cSentMsgs);
		PostMessage(phsctx->hWnd, HM_WORKERTHREAD_UPDATE, (WPARAM)phsctx, (LPARAM)pItem);
    };
#pragma warning(pop)

    try
    {
#ifdef USE_PPL
        if (bMultithreaded)
            concurrency::parallel_for_each(vecpItems.cbegin(), vecpItems.cend(), per_file_worker);
        else
#endif
            std::for_each(vecpItems.cbegin(), vecpItems.cend(), per_file_worker);
    }
    catch (CanceledException) {}  // ignore cancellation requests

#ifdef _TIMED
    if (phsctx->cTotal > 1 && phsctx->status != CANCEL_REQUESTED)
    {
        union {
            CHAR  szA[MAX_STRINGMSG];
            WCHAR szW[MAX_STRINGMSG];
        } buffer;
        size_t cbBufferLeft;
        if (phsctx->opt.dwSaveEncoding == 1)  // UTF-16
        {
            StringCbPrintfExW(buffer.szW, sizeof(buffer), NULL, &cbBufferLeft, 0, L"; Total elapsed: %d ms\r\n", GetTickCount() - dwStarted);
        }
        else                                  // UTF-8 or ANSI
        {
            StringCbPrintfExA(buffer.szA, sizeof(buffer), NULL, &cbBufferLeft, 0,  "; Total elapsed: %d ms\r\n", GetTickCount() - dwStarted);
        }
        DWORD dwUnused;
        WriteFile(phsctx->hFileOut, buffer.szA, (DWORD) (sizeof(buffer) - cbBufferLeft), &dwUnused, NULL);
    }
#endif

#ifdef USE_PPL
    if (bMultithreaded)
    {
        for (void* pBuffer : vecBuffers)
            VirtualFree(pBuffer, 0, MEM_RELEASE);
        DeleteCriticalSection(&updateCritSec);
    }
    else
#endif
        VirtualFree(pbTheBuffer, 0, MEM_RELEASE);
}