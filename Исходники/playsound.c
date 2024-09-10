static DWORD WINAPI proc_PlaySound(LPVOID arg)
{
    WINE_PLAYSOUND*     wps = arg;
    BOOL		bRet = FALSE;
    HMMIO		hmmio = 0;
    MMCKINFO		ckMainRIFF;
    MMCKINFO        	mmckInfo;
    LPWAVEFORMATEX      lpWaveFormat = NULL;
    HWAVEOUT		hWave = 0;
    LPWAVEHDR		waveHdr = NULL;
    INT			count, bufsize, left, index;
    struct playsound_data	s;
    void*               data;

    s.hEvent = 0;

    TRACE("SoundName=%s !\n", debugstr_w(wps->pszSound));

    /* if resource, grab it */
    if ((wps->fdwSound & SND_RESOURCE) == SND_RESOURCE) {
        static const WCHAR wszWave[] = {'W','A','V','E',0};
        HRSRC	hRes;
        HGLOBAL	hGlob;

        if ((hRes = FindResourceW(wps->hMod, wps->pszSound, wszWave)) == 0 ||
            (hGlob = LoadResource(wps->hMod, hRes)) == 0)
            goto errCleanUp;
        if ((data = LockResource(hGlob)) == NULL) {
            FreeResource(hGlob);
            goto errCleanUp;
        }
        FreeResource(hGlob);
    } else
        data = (void*)wps->pszSound;

    /* construct an MMIO stream (either in memory, or from a file */
    if (wps->fdwSound & SND_MEMORY)
    { /* NOTE: SND_RESOURCE has the SND_MEMORY bit set */
	MMIOINFO	mminfo;

	memset(&mminfo, 0, sizeof(mminfo));
	mminfo.fccIOProc = FOURCC_MEM;
	mminfo.pchBuffer = data;
	mminfo.cchBuffer = -1; /* FIXME: when a resource, could grab real size */
	TRACE("Memory sound %p\n", data);
	hmmio = mmioOpenW(NULL, &mminfo, MMIO_READ);
    }
    if (!hmmio && wps->fdwSound & SND_ALIAS)
    {
        if ((wps->fdwSound & SND_ALIAS_ID) == SND_ALIAS_ID)
        {
            static const WCHAR  wszSystemAsterisk[] = {'S','y','s','t','e','m','A','s','t','e','r','i','s','k',0};
            static const WCHAR  wszSystemDefault[] = {'S','y','s','t','e','m','D','e','f','a','u','l','t',0};
            static const WCHAR  wszSystemExclamation[] = {'S','y','s','t','e','m','E','x','c','l','a','m','a','t','i','o','n',0};
            static const WCHAR  wszSystemExit[] = {'S','y','s','t','e','m','E','x','i','t',0};
            static const WCHAR  wszSystemHand[] = {'S','y','s','t','e','m','H','a','n','d',0};
            static const WCHAR  wszSystemQuestion[] = {'S','y','s','t','e','m','Q','u','e','s','t','i','o','n',0};
            static const WCHAR  wszSystemStart[] = {'S','y','s','t','e','m','S','t','a','r','t',0};
            static const WCHAR  wszSystemWelcome[] = {'S','y','s','t','e','m','W','e','l','c','o','m','e',0};

            wps->fdwSound &= ~(SND_ALIAS_ID ^ SND_ALIAS);
            if (wps->pszSound == (LPCWSTR)SND_ALIAS_SYSTEMASTERISK)
                wps->pszSound = wszSystemAsterisk;
            else if (wps->pszSound == (LPCWSTR)SND_ALIAS_SYSTEMDEFAULT)
                wps->pszSound = wszSystemDefault;
            else if (wps->pszSound == (LPCWSTR)SND_ALIAS_SYSTEMEXCLAMATION)
                wps->pszSound = wszSystemExclamation;
            else if (wps->pszSound == (LPCWSTR)SND_ALIAS_SYSTEMEXIT)
                wps->pszSound = wszSystemExit;
            else if (wps->pszSound == (LPCWSTR)SND_ALIAS_SYSTEMHAND)
                wps->pszSound = wszSystemHand;
            else if (wps->pszSound == (LPCWSTR)SND_ALIAS_SYSTEMQUESTION)
                wps->pszSound = wszSystemQuestion;
            else if (wps->pszSound == (LPCWSTR)SND_ALIAS_SYSTEMSTART)
                wps->pszSound = wszSystemStart;
            else if (wps->pszSound == (LPCWSTR)SND_ALIAS_SYSTEMWELCOME)
                wps->pszSound = wszSystemWelcome;
            else goto errCleanUp;
        }
        hmmio = get_mmioFromProfile(wps->fdwSound, wps->pszSound);
        if (!hmmio)
        {
            wps->fdwSound &= ~SND_ALIAS;
            wps->fdwSound |= SND_FILENAME;
        }
    }
    if (!hmmio && wps->fdwSound & SND_FILENAME)
    {
        hmmio = get_mmioFromFile(wps->pszSound);
    }
    if (!(wps->fdwSound & (SND_FILENAME|SND_ALIAS|SND_MEMORY)))
    {
        if ((hmmio = get_mmioFromProfile(wps->fdwSound | SND_NODEFAULT, wps->pszSound)) == 0)
        {
            if ((hmmio = get_mmioFromFile(wps->pszSound)) == 0)
            {
                hmmio = get_mmioFromProfile(wps->fdwSound, wps->pszSound);
            }
        }
    }
    if (hmmio == 0) goto errCleanUp;

    if (mmioDescend(hmmio, &ckMainRIFF, NULL, 0))
	goto errCleanUp;

    TRACE("ParentChunk ckid=%.4s fccType=%.4s cksize=%08X\n",
	  (LPSTR)&ckMainRIFF.ckid, (LPSTR)&ckMainRIFF.fccType, ckMainRIFF.cksize);

    if ((ckMainRIFF.ckid != FOURCC_RIFF) ||
	(ckMainRIFF.fccType != mmioFOURCC('W', 'A', 'V', 'E')))
	goto errCleanUp;

    mmckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if (mmioDescend(hmmio, &mmckInfo, &ckMainRIFF, MMIO_FINDCHUNK))
	goto errCleanUp;

    TRACE("Chunk Found ckid=%.4s fccType=%08x cksize=%08X\n",
	  (LPSTR)&mmckInfo.ckid, mmckInfo.fccType, mmckInfo.cksize);

    lpWaveFormat = HeapAlloc(GetProcessHeap(), 0, mmckInfo.cksize);
    if (!lpWaveFormat)
	goto errCleanUp;
    if (mmioRead(hmmio, (HPSTR)lpWaveFormat, mmckInfo.cksize) < sizeof(PCMWAVEFORMAT))
	goto errCleanUp;

    TRACE("wFormatTag=%04X !\n", 	lpWaveFormat->wFormatTag);
    TRACE("nChannels=%d\n", 		lpWaveFormat->nChannels);
    TRACE("nSamplesPerSec=%d\n", 	lpWaveFormat->nSamplesPerSec);
    TRACE("nAvgBytesPerSec=%d\n", 	lpWaveFormat->nAvgBytesPerSec);
    TRACE("nBlockAlign=%d\n", 		lpWaveFormat->nBlockAlign);
    TRACE("wBitsPerSample=%u !\n", 	lpWaveFormat->wBitsPerSample);

    /* move to end of 'fmt ' chunk */
    mmioAscend(hmmio, &mmckInfo, 0);

    mmckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
    if (mmioDescend(hmmio, &mmckInfo, &ckMainRIFF, MMIO_FINDCHUNK))
	goto errCleanUp;

    TRACE("Chunk Found ckid=%.4s fccType=%08x cksize=%08X\n",
	  (LPSTR)&mmckInfo.ckid, mmckInfo.fccType, mmckInfo.cksize);

    s.hEvent = CreateEventW(NULL, FALSE, FALSE, NULL);
    if (!s.hEvent || bPlaySoundStop)
	goto errCleanUp;

    if (waveOutOpen(&hWave, WAVE_MAPPER, lpWaveFormat, (DWORD_PTR)PlaySound_Callback,
		    (DWORD_PTR)&s, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
	goto errCleanUp;

    /* make it so that 3 buffers per second are needed */
    bufsize = (((lpWaveFormat->nAvgBytesPerSec / 3) - 1) / lpWaveFormat->nBlockAlign + 1) *
	lpWaveFormat->nBlockAlign;
    waveHdr = HeapAlloc(GetProcessHeap(), 0, 2 * sizeof(WAVEHDR) + 2 * bufsize);
    if (!waveHdr)
	goto errCleanUp;
    waveHdr[0].lpData = (char*)waveHdr + 2 * sizeof(WAVEHDR);
    waveHdr[1].lpData = (char*)waveHdr + 2 * sizeof(WAVEHDR) + bufsize;
    waveHdr[0].dwUser = waveHdr[1].dwUser = 0L;
    waveHdr[0].dwLoops = waveHdr[1].dwLoops = 0L;
    waveHdr[0].dwFlags = waveHdr[1].dwFlags = 0L;
    waveHdr[0].dwBufferLength = waveHdr[1].dwBufferLength = bufsize;
    if (waveOutPrepareHeader(hWave, &waveHdr[0], sizeof(WAVEHDR)) ||
	waveOutPrepareHeader(hWave, &waveHdr[1], sizeof(WAVEHDR))) {
	goto errCleanUp;
    }

    wps->hWave = hWave;
    s.dwEventCount = 1L; /* for first buffer */
    index = 0;

    do {
	left = mmckInfo.cksize;

	mmioSeek(hmmio, mmckInfo.dwDataOffset, SEEK_SET);
	while (left)
        {
	    if (bPlaySoundStop)
            {
		wps->bLoop = FALSE;
		break;
	    }
	    count = mmioRead(hmmio, waveHdr[index].lpData, min(bufsize, left));
	    if (count < 1) break;
	    left -= count;
	    waveHdr[index].dwBufferLength = count;
	    if (waveOutWrite(hWave, &waveHdr[index], sizeof(WAVEHDR)) == MMSYSERR_NOERROR) {
                index ^= 1;
                PlaySound_WaitDone(&s);
            }
            else {
		ERR("Aborting play loop, waveOutWrite error\n");
		wps->bLoop = FALSE;
		break;
	    }
	}
	bRet = TRUE;
    } while (wps->bLoop);

    PlaySound_WaitDone(&s); /* to balance first buffer */
    waveOutReset(hWave);

    waveOutUnprepareHeader(hWave, &waveHdr[0], sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWave, &waveHdr[1], sizeof(WAVEHDR));

errCleanUp:
    TRACE("Done playing=%s => %s!\n", debugstr_w(wps->pszSound), bRet ? "ok" : "ko");
    HeapFree(GetProcessHeap(), 0, lpWaveFormat);
    if (hWave)
    {
        EnterCriticalSection(&WINMM_cs);
        /* the CS prevents a concurrent waveOutReset */
        wps->hWave = 0;
        LeaveCriticalSection(&WINMM_cs);
        while (waveOutClose(hWave) == WAVERR_STILLPLAYING)
            Sleep(100);
    }
    CloseHandle(s.hEvent);
    HeapFree(GetProcessHeap(), 0, waveHdr);
    if (hmmio) 		mmioClose(hmmio, 0);

    PlaySound_Free(wps);

    return bRet;
}