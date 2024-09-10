static HRESULT AVIFILE_SaveFile(const IAVIFileImpl *This)
{
  MMCKINFO ckRIFF;
  MMCKINFO ck;

  mmioSeek(This->hmmio, 0, SEEK_SET);

  /* create the RIFF chunk with formtype WAVE */
  ckRIFF.fccType = formtypeWAVE;
  ckRIFF.cksize  = 0;
  if (mmioCreateChunk(This->hmmio, &ckRIFF, MMIO_CREATERIFF) != S_OK)
    return AVIERR_FILEWRITE;

  /* the next chunk is the format */
  ck.ckid   = ckidWAVEFORMAT;
  ck.cksize = This->cbFormat;
  if (mmioCreateChunk(This->hmmio, &ck, 0) != S_OK)
    return AVIERR_FILEWRITE;
  if (This->lpFormat != NULL && This->cbFormat > 0) {
    if (mmioWrite(This->hmmio, (HPSTR)This->lpFormat, ck.cksize) != ck.cksize)
      return AVIERR_FILEWRITE;
  }
  if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
    return AVIERR_FILEWRITE;

  /* fact chunk is needed for non-pcm waveforms */
  if (This->lpFormat != NULL && This->cbFormat > sizeof(PCMWAVEFORMAT) &&
      This->lpFormat->wFormatTag != WAVE_FORMAT_PCM) {
    WAVEFORMATEX wfx;
    DWORD        dwFactLength;
    HACMSTREAM   has;

    /* try to open an appropriate audio codec to figure out
     * data for fact-chunk */
    wfx.wFormatTag = WAVE_FORMAT_PCM;
    if (acmFormatSuggest(NULL, This->lpFormat, &wfx,
			 sizeof(wfx), ACM_FORMATSUGGESTF_WFORMATTAG)) {
      acmStreamOpen(&has, NULL, This->lpFormat, &wfx, NULL,
		    0, 0, ACM_STREAMOPENF_NONREALTIME);
      acmStreamSize(has, This->ckData.cksize, &dwFactLength,
		    ACM_STREAMSIZEF_SOURCE);
      dwFactLength /= wfx.nBlockAlign;
      acmStreamClose(has, 0);

      /* create the fact chunk */
      ck.ckid   = ckidWAVEFACT;
      ck.cksize = sizeof(dwFactLength);

      /* test for enough space before data chunk */
      if (mmioSeek(This->hmmio, 0, SEEK_CUR) > This->ckData.dwDataOffset
	  - ck.cksize - 4 * sizeof(DWORD))
	return AVIERR_FILEWRITE;
      if (mmioCreateChunk(This->hmmio, &ck, 0) != S_OK)
	return AVIERR_FILEWRITE;
      if (mmioWrite(This->hmmio, (HPSTR)&dwFactLength, ck.cksize) != ck.cksize)
	return AVIERR_FILEWRITE;
      if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
	return AVIERR_FILEWRITE;
    } else
      ERR(": fact chunk is needed for non-pcm files -- currently no codec found, so skipped!\n");
  }

  /* if there was extra stuff, we need to fill it with JUNK */
  if (mmioSeek(This->hmmio, 0, SEEK_CUR) + 2 * sizeof(DWORD) < This->ckData.dwDataOffset) {
    ck.ckid   = ckidAVIPADDING;
    ck.cksize = 0;
    if (mmioCreateChunk(This->hmmio, &ck, 0) != S_OK)
      return AVIERR_FILEWRITE;

    if (mmioSeek(This->hmmio, This->ckData.dwDataOffset
		 - 2 * sizeof(DWORD), SEEK_SET) == -1)
      return AVIERR_FILEWRITE;
    if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
      return AVIERR_FILEWRITE;
  }

  /* create the data chunk */
  ck.ckid   = ckidWAVEDATA;
  ck.cksize = This->ckData.cksize;
  if (mmioCreateChunk(This->hmmio, &ck, 0) != S_OK)
    return AVIERR_FILEWRITE;
  if (mmioSeek(This->hmmio, This->ckData.cksize, SEEK_CUR) == -1)
    return AVIERR_FILEWRITE;
  if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
    return AVIERR_FILEWRITE;

  /* some optional extra chunks? */
  if (This->extra.lp != NULL && This->extra.cb > 0) {
    /* chunk headers are already in structure */
    if (mmioWrite(This->hmmio, This->extra.lp, This->extra.cb) != This->extra.cb)
      return AVIERR_FILEWRITE;
  }

  /* close RIFF chunk */
  if (mmioAscend(This->hmmio, &ckRIFF, 0) != S_OK)
    return AVIERR_FILEWRITE;
  if (mmioFlush(This->hmmio, 0) != S_OK)
    return AVIERR_FILEWRITE;

  return AVIERR_OK;
}