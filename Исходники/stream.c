/***********************************************************************
 *           acmStreamPrepareHeader (MSACM32.@)
 */
MMRESULT WINAPI acmStreamPrepareHeader(HACMSTREAM has, PACMSTREAMHEADER pash,
				       DWORD fdwPrepare)
{
    PWINE_ACMSTREAM	was;
    MMRESULT		ret = MMSYSERR_NOERROR;
    PACMDRVSTREAMHEADER	padsh;

    TRACE("(%p, %p, %d)\n", has, pash, fdwPrepare);

    if ((was = ACM_GetStream(has)) == NULL) {
        WARN("invalid handle\n");
        return MMSYSERR_INVALHANDLE;
    }
    if (!pash || pash->cbStruct < sizeof(ACMSTREAMHEADER)) {
        WARN("invalid parameter\n");
        return MMSYSERR_INVALPARAM;
    }
    if (fdwPrepare) {
        WARN("invalid use of reserved parameter\n");
        return MMSYSERR_INVALFLAG;
    }
    if ((was->drvInst.pwfxSrc->wFormatTag == WAVE_FORMAT_ADPCM ||
         was->drvInst.pwfxSrc->wFormatTag == WAVE_FORMAT_PCM) &&
        pash->cbSrcLength < was->drvInst.pwfxSrc->nBlockAlign) {
        WARN("source smaller than block align (%d < %d)\n",
             pash->cbSrcLength, was->drvInst.pwfxSrc->nBlockAlign);
        return pash->cbSrcLength ? ACMERR_NOTPOSSIBLE : MMSYSERR_INVALPARAM;
    }

    /* Note: the ACMSTREAMHEADER and ACMDRVSTREAMHEADER structs are of same
     * size. some fields are private to msacm internals, and are exposed
     * in ACMSTREAMHEADER in the dwReservedDriver array
     */
    padsh = (PACMDRVSTREAMHEADER)pash;

    padsh->fdwConvert = fdwPrepare;
    padsh->padshNext = NULL;
    padsh->fdwDriver = padsh->dwDriver = 0L;

    padsh->fdwPrepared = 0;
    padsh->dwPrepared = 0;
    padsh->pbPreparedSrc = 0;
    padsh->cbPreparedSrcLength = 0;
    padsh->pbPreparedDst = 0;
    padsh->cbPreparedDstLength = 0;

    ret = MSACM_Message((HACMDRIVER)was->pDrv, ACMDM_STREAM_PREPARE, (LPARAM)&was->drvInst, (LPARAM)padsh);
    if (ret == MMSYSERR_NOERROR || ret == MMSYSERR_NOTSUPPORTED) {
	ret = MMSYSERR_NOERROR;
	padsh->fdwStatus &= ~ACMSTREAMHEADER_STATUSF_INQUEUE;
	padsh->fdwStatus |= ACMSTREAMHEADER_STATUSF_PREPARED;
	padsh->fdwPrepared = padsh->fdwStatus;
	padsh->dwPrepared = 0;
	padsh->pbPreparedSrc = padsh->pbSrc;
	padsh->cbPreparedSrcLength = padsh->cbSrcLength;
	padsh->pbPreparedDst = padsh->pbDst;
	padsh->cbPreparedDstLength = padsh->cbDstLength;
    } else {
	padsh->fdwPrepared = 0;
	padsh->dwPrepared = 0;
	padsh->pbPreparedSrc = 0;
	padsh->cbPreparedSrcLength = 0;
	padsh->pbPreparedDst = 0;
	padsh->cbPreparedDstLength = 0;
    }
    TRACE("=> (%d)\n", ret);
    return ret;
}