static	DWORD	widUnprepare(WAVEMAPDATA* wim, LPWAVEHDR lpWaveHdrDst, DWORD dwParam2)
{
    PACMSTREAMHEADER	ash;
    LPWAVEHDR		lpWaveHdrSrc;
    DWORD		dwRet1, dwRet2;

    TRACE("(%p %p %08x)\n", wim, lpWaveHdrDst, dwParam2);

    if (!wim->hAcmStream) {
	return waveInUnprepareHeader(wim->u.in.hInnerWave, lpWaveHdrDst, dwParam2);
    }
    ash = (PACMSTREAMHEADER)lpWaveHdrDst->reserved;
    dwRet1 = acmStreamUnprepareHeader(wim->hAcmStream, ash, 0L);

    lpWaveHdrSrc = (LPWAVEHDR)((LPSTR)ash + sizeof(ACMSTREAMHEADER));
    dwRet2 = waveInUnprepareHeader(wim->u.in.hInnerWave, lpWaveHdrSrc, sizeof(*lpWaveHdrSrc));

    HeapFree(GetProcessHeap(), 0, ash);

    lpWaveHdrDst->dwFlags &= ~WHDR_PREPARED;
    return (dwRet1 == MMSYSERR_NOERROR) ? dwRet2 : dwRet1;
}