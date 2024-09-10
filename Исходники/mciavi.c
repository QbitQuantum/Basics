/***************************************************************************
 * 				MCIAVI_mciPlay			[internal]
 */
static	DWORD	MCIAVI_mciPlay(UINT wDevID, DWORD dwFlags, LPMCI_PLAY_PARMS lpParms)
{
    WINE_MCIAVI *wma;
    DWORD		frameTime;
    DWORD		dwRet;
    LPWAVEHDR		waveHdr = NULL;
    unsigned		i, nHdr = 0;
    DWORD		dwFromFrame, dwToFrame;
    DWORD		numEvents = 1;
    HANDLE		events[2];

    TRACE("(%04x, %08X, %p)\n", wDevID, dwFlags, lpParms);

    if (lpParms == NULL)	return MCIERR_NULL_PARAMETER_BLOCK;

    wma = MCIAVI_mciGetOpenDev(wDevID);
    if (wma == NULL)		return MCIERR_INVALID_DEVICE_ID;
    if (dwFlags & MCI_DGV_PLAY_REVERSE) return MCIERR_UNSUPPORTED_FUNCTION;
    if (dwFlags & MCI_TEST)	return 0;

    EnterCriticalSection(&wma->cs);

    if (!wma->hFile)
    {
        LeaveCriticalSection(&wma->cs);
        return MCIERR_FILE_NOT_FOUND;
    }
    if (!wma->hWndPaint)
    {
        LeaveCriticalSection(&wma->cs);
        return MCIERR_NO_WINDOW;
    }

    LeaveCriticalSection(&wma->cs);

    if (!(dwFlags & MCI_WAIT))
        return MCIAVI_mciPlay_async(wma, dwFlags, lpParms);

    if (!(GetWindowLongW(wma->hWndPaint, GWL_STYLE) & WS_VISIBLE))
        ShowWindow(wma->hWndPaint, SW_SHOWNA);

    EnterCriticalSection(&wma->cs);

    dwFromFrame = wma->dwCurrVideoFrame;
    dwToFrame = wma->dwPlayableVideoFrames - 1;

    if (lpParms && (dwFlags & MCI_FROM)) {
	dwFromFrame = MCIAVI_ConvertTimeFormatToFrame(wma, lpParms->dwFrom);
    }
    if (lpParms && (dwFlags & MCI_TO)) {
	dwToFrame = MCIAVI_ConvertTimeFormatToFrame(wma, lpParms->dwTo);
    }
    if (dwToFrame >= wma->dwPlayableVideoFrames)
	dwToFrame = wma->dwPlayableVideoFrames - 1;

    TRACE("Playing from frame=%u to frame=%u\n", dwFromFrame, dwToFrame);

    wma->dwCurrVideoFrame = dwFromFrame;
    wma->dwToVideoFrame = dwToFrame;

    /* if already playing exit */
    if (wma->dwStatus == MCI_MODE_PLAY)
    {
        LeaveCriticalSection(&wma->cs);
        SetEvent(wma->ack_event);
        return 0;
    }

    if (wma->dwToVideoFrame <= wma->dwCurrVideoFrame)
    {
        dwRet = 0;
        SetEvent(wma->ack_event);
        goto mci_play_done;
    }

    wma->dwStatus = MCI_MODE_PLAY;
    /* signal the state change */
    SetEvent(wma->ack_event);

    if (dwFlags & (MCI_DGV_PLAY_REPEAT|MCI_MCIAVI_PLAY_WINDOW|MCI_MCIAVI_PLAY_FULLSCREEN))
	FIXME("Unsupported flag %08x\n", dwFlags);

    /* time is in microseconds, we should convert it to milliseconds */
    frameTime = (wma->mah.dwMicroSecPerFrame + 500) / 1000;

    events[0] = wma->hStopEvent;
    if (wma->lpWaveFormat) {
       if (MCIAVI_OpenAudio(wma, &nHdr, &waveHdr) != 0)
        {
            /* can't play audio */
            HeapFree(GetProcessHeap(), 0, wma->lpWaveFormat);
            wma->lpWaveFormat = NULL;
        }
       else
       {
            /* fill the queue with as many wave headers as possible */
            MCIAVI_PlayAudioBlocks(wma, nHdr, waveHdr);
            events[1] = wma->hEvent;
            numEvents = 2;
       }
    }

    while (wma->dwStatus == MCI_MODE_PLAY)
    {
        HDC hDC;
        DWORD tc, delta;
        DWORD ret;

	tc = GetTickCount();

        hDC = wma->hWndPaint ? GetDC(wma->hWndPaint) : 0;
        if (hDC)
        {
            MCIAVI_PaintFrame(wma, hDC);
            ReleaseDC(wma->hWndPaint, hDC);
        }

        if (wma->lpWaveFormat)
	    MCIAVI_PlayAudioBlocks(wma, nHdr, waveHdr);

	delta = GetTickCount() - tc;
	if (delta < frameTime)
            delta = frameTime - delta;
        else
            delta = 0;

        LeaveCriticalSection(&wma->cs);
        ret = WaitForMultipleObjects(numEvents, events, FALSE, delta);
        EnterCriticalSection(&wma->cs);
        if (ret == WAIT_OBJECT_0 || wma->dwStatus != MCI_MODE_PLAY) break;

       if (wma->dwCurrVideoFrame < dwToFrame)
           wma->dwCurrVideoFrame++;
        else
            break;
    }

    if (wma->lpWaveFormat) {
       while (wma->dwEventCount != nHdr - 1)
        {
            LeaveCriticalSection(&wma->cs);
            Sleep(100);
            EnterCriticalSection(&wma->cs);
        }

	/* just to get rid of some race conditions between play, stop and pause */
	LeaveCriticalSection(&wma->cs);
	waveOutReset(wma->hWave);
	EnterCriticalSection(&wma->cs);

	for (i = 0; i < nHdr; i++)
	    waveOutUnprepareHeader(wma->hWave, &waveHdr[i], sizeof(WAVEHDR));
    }

    dwRet = 0;

    if (wma->lpWaveFormat) {
	HeapFree(GetProcessHeap(), 0, waveHdr);

	if (wma->hWave) {
	    LeaveCriticalSection(&wma->cs);
	    waveOutClose(wma->hWave);
	    EnterCriticalSection(&wma->cs);
	    wma->hWave = 0;
	}
	CloseHandle(wma->hEvent);
    }

mci_play_done:
    wma->dwStatus = MCI_MODE_STOP;

    if (lpParms && (dwFlags & MCI_NOTIFY)) {
	TRACE("MCI_NOTIFY_SUCCESSFUL %08lX !\n", lpParms->dwCallback);
	mciDriverNotify(HWND_32(LOWORD(lpParms->dwCallback)),
                       wDevID, MCI_NOTIFY_SUCCESSFUL);
    }
    LeaveCriticalSection(&wma->cs);
    return dwRet;
}