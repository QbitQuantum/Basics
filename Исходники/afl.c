/***********************************************************************
 *           acmStreamOpen (MSACM32.40)
 */
MMRESULT WINAPI acmStreamOpen(PHACMSTREAM phas, HACMDRIVER had, PWAVEFORMATEX pwfxSrc,
			      PWAVEFORMATEX pwfxDst, PWAVEFILTER pwfltr, DWORD dwCallback,
			      DWORD dwInstance, DWORD fdwOpen)
{
    PWINE_ACMSTREAM	was;
    PWINE_ACMDRIVER	wad;
    MMRESULT		ret;
    int			wfxSrcSize;
    int			wfxDstSize;
    
    TRACE("(%p, 0x%08x, %p, %p, %p, %ld, %ld, %ld)\n",
	  phas, had, pwfxSrc, pwfxDst, pwfltr, dwCallback, dwInstance, fdwOpen);

    TRACE("src [wFormatTag=%u, nChannels=%u, nSamplesPerSec=%lu, nAvgBytesPerSec=%lu, nBlockAlign=%u, wBitsPerSample=%u, cbSize=%u]\n", 
	  pwfxSrc->wFormatTag, pwfxSrc->nChannels, pwfxSrc->nSamplesPerSec, pwfxSrc->nAvgBytesPerSec, 
	  pwfxSrc->nBlockAlign, pwfxSrc->wBitsPerSample, pwfxSrc->cbSize);

    TRACE("dst [wFormatTag=%u, nChannels=%u, nSamplesPerSec=%lu, nAvgBytesPerSec=%lu, nBlockAlign=%u, wBitsPerSample=%u, cbSize=%u]\n", 
	  pwfxDst->wFormatTag, pwfxDst->nChannels, pwfxDst->nSamplesPerSec, pwfxDst->nAvgBytesPerSec, 
	  pwfxDst->nBlockAlign, pwfxDst->wBitsPerSample, pwfxDst->cbSize);

#define SIZEOF_WFX(wfx) (sizeof(WAVEFORMATEX) + ((wfx->wFormatTag == WAVE_FORMAT_PCM) ? 0 : wfx->cbSize))
    wfxSrcSize = SIZEOF_WFX(pwfxSrc);
    wfxDstSize = SIZEOF_WFX(pwfxDst);
#undef SIZEOF_WFX

    was = (PWINE_ACMSTREAM) HeapAlloc(MSACM_hHeap, 0, sizeof(*was) + wfxSrcSize + wfxDstSize + ((pwfltr) ? sizeof(WAVEFILTER) : 0));
    if (was == NULL)
	return MMSYSERR_NOMEM;
    was->drvInst.cbStruct = sizeof(was->drvInst);
    was->drvInst.pwfxSrc = (PWAVEFORMATEX)((LPSTR)was + sizeof(*was));
    memcpy(was->drvInst.pwfxSrc, pwfxSrc, wfxSrcSize);
    // LHACM is checking for 0x1
    // but if this will not help
    // was->drvInst.pwfxSrc->wFormatTag = 1;
    was->drvInst.pwfxDst = (PWAVEFORMATEX)((LPSTR)was + sizeof(*was) + wfxSrcSize);
    memcpy(was->drvInst.pwfxDst, pwfxDst, wfxDstSize);
    if (pwfltr) {
	was->drvInst.pwfltr = (PWAVEFILTER)((LPSTR)was + sizeof(*was) + wfxSrcSize + wfxDstSize);
	memcpy(was->drvInst.pwfltr, pwfltr, sizeof(WAVEFILTER));
    } else {
	was->drvInst.pwfltr = NULL;
    }
    was->drvInst.dwCallback = dwCallback;    
    was->drvInst.dwInstance = dwInstance;
    was->drvInst.fdwOpen = fdwOpen;
    was->drvInst.fdwDriver = 0L;  
    was->drvInst.dwDriver = 0L;     
    was->drvInst.has = (HACMSTREAM)was;
    
    if (had) {
	if (!(wad = MSACM_GetDriver(had))) {
	    ret = MMSYSERR_INVALPARAM;
	    goto errCleanUp;
	}
	
	was->obj.pACMDriverID = wad->obj.pACMDriverID;
	was->pDrv = wad;
	was->hAcmDriver = 0; /* not to close it in acmStreamClose */

	ret = SendDriverMessage(wad->hDrvr, ACMDM_STREAM_OPEN, (DWORD)&was->drvInst, 0L);
	if (ret != MMSYSERR_NOERROR)
	    goto errCleanUp;
    } else {
	PWINE_ACMDRIVERID wadi;
	/* short drv_tag; -- not used */
	ret = ACMERR_NOTPOSSIBLE;
/*	if(pwfxSrc->wFormatTag==1)//compression
	    drv_tag=pwfxDst->wFormatTag;
	    else
	    if(pwfxDst->wFormatTag==1)//decompression
		drv_tag=pwfxSrc->wFormatTag;
		else
		goto errCleanUp;

	    ret=acmDriverOpen2(drv_tag); 
	    if (ret == MMSYSERR_NOERROR) {
		if ((wad = MSACM_GetDriver(had)) != 0) {
		    was->obj.pACMDriverID = wad->obj.pACMDriverID;
		    was->pDrv = wad;
		    was->hAcmDriver = had;
		    
		    ret = SendDriverMessage(wad->hDrvr, ACMDM_STREAM_OPEN, (DWORD)&was->drvInst, 0L);
		    if (ret == MMSYSERR_NOERROR) {
			if (fdwOpen & ACM_STREAMOPENF_QUERY) {
			    acmDriverClose(had, 0L);
			}
			break;
		    }
		}
		acmDriverClose(had, 0L);*/
	//if(MSACM_pFirstACMDriverID==NULL)
	//    MSACM_RegisterAllDrivers();
	
	for (wadi = MSACM_pFirstACMDriverID; wadi; wadi = wadi->pNextACMDriverID)
	{
	    /* Check Format */
	    if ((int)wadi->wFormatTag != (int)pwfxSrc->wFormatTag) continue;

	    ret = acmDriverOpen(&had, (HACMDRIVERID)wadi, 0L);
	    if (ret == MMSYSERR_NOERROR) {
		if ((wad = MSACM_GetDriver(had)) != 0) {
		    was->obj.pACMDriverID = wad->obj.pACMDriverID;
		    was->pDrv = wad;
		    was->hAcmDriver = had;
		    
		    ret = SendDriverMessage(wad->hDrvr, ACMDM_STREAM_OPEN, (DWORD)&was->drvInst, 0L);
		    //lhacm - crash printf("RETOPEN %d\n", ret);
                    //ret = 0;
		    if (ret == MMSYSERR_NOERROR) {
			if (fdwOpen & ACM_STREAMOPENF_QUERY) {
			    acmDriverClose(had, 0L);
			}
			break;
		    }
		}
		// no match, close this acm driver and try next one 
		acmDriverClose(had, 0L);
	    }
	}
	if (ret != MMSYSERR_NOERROR) {
	    ret = ACMERR_NOTPOSSIBLE;
	    goto errCleanUp;
	}
    }
    ret = MMSYSERR_NOERROR;
    if (!(fdwOpen & ACM_STREAMOPENF_QUERY)) {
	if (phas)
	    *phas = (HACMSTREAM)was;
	TRACE("=> (%d)\n", ret);
	CodecAlloc();
	return ret;
    }
errCleanUp:		
    if (phas)
	*phas = (HACMSTREAM)0;
    HeapFree(MSACM_hHeap, 0, was);
    TRACE("=> (%d)\n", ret);
    return ret;
}