/* reads all non-junk chunks into the extrachunk-structure until it finds
 * the given chunk or the optional parent-chunk is at the end */
HRESULT FindChunkAndKeepExtras(LPEXTRACHUNKS extra,HMMIO hmmio,MMCKINFO *lpck,
			       MMCKINFO *lpckParent,UINT flags)
{
  FOURCC  ckid;
  FOURCC  fccType;
  HRESULT hr;

  /* pre-conditions */
  assert(extra != NULL);
  assert(hmmio != NULL);
  assert(lpck  != NULL);

  TRACE("({%p,%lu},%p,%p,%p,0x%X)\n", extra->lp, extra->cb, hmmio, lpck,
	lpckParent, flags);

  /* what chunk id and form/list type should we search? */
  if (flags & MMIO_FINDCHUNK) {
    ckid    = lpck->ckid;
    fccType = 0;
  } else if (flags & MMIO_FINDLIST) {
    ckid    = FOURCC_LIST;
    fccType = lpck->fccType;
  } else if (flags & MMIO_FINDRIFF) {
    ckid    = FOURCC_RIFF;
    fccType = lpck->fccType;
  } else
    ckid = fccType = (FOURCC)-1; /* collect everything into extra! */

  TRACE(": find ckid=0x%08lX fccType=0x%08lX\n", ckid, fccType);

  for (;;) {
    hr = mmioDescend(hmmio, lpck, lpckParent, 0);
    if (hr != S_OK) {
      /* No extra chunks in front of desired chunk? */
      if (flags == 0 && hr == MMIOERR_CHUNKNOTFOUND)
	hr = AVIERR_OK;
      return hr;
    }

    /* Have we found what we search for? */
    if ((lpck->ckid == ckid) &&
	(fccType == (FOURCC)0 || lpck->fccType == fccType))
      return AVIERR_OK;

    /* Skip padding chunks, the others put into the extrachunk-structure */
    if (lpck->ckid == ckidAVIPADDING ||
	lpck->ckid == mmioFOURCC('p','a','d','d'))
      hr = mmioAscend(hmmio, lpck, 0);
    else
      hr = ReadChunkIntoExtra(extra, hmmio, lpck);
    if (FAILED(hr))
      return hr;
  }
}