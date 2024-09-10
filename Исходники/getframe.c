static LPVOID  WINAPI IGetFrame_fnGetFrame(IGetFrame *iface, LONG lPos)
{
  IGetFrameImpl *This = impl_from_IGetFrame(iface);

  LONG readBytes;
  LONG readSamples;

  TRACE("(%p,%d)\n", iface, lPos);

  /* We don't want negative start values! -- marks invalid buffer content */
  if (lPos < 0)
    return NULL;

  /* check state */
  if (This->pStream == NULL)
    return NULL;
  if (This->lpInFormat == NULL)
    return NULL;

  /* Could stream have changed? */
  if (! This->bFixedStream) {
    AVISTREAMINFOW sInfo;

    IAVIStream_Info(This->pStream, &sInfo, sizeof(sInfo));

    if (sInfo.dwEditCount != This->dwEditCount) {
      This->dwEditCount   = sInfo.dwEditCount;
      This->lCurrentFrame = -1;
    }

    if (sInfo.dwFormatChangeCount != This->dwFormatChangeCount) {
      /* stream has changed */
      if (This->lpOutFormat != NULL) {
	BITMAPINFOHEADER bi;

	bi = *This->lpOutFormat;
	AVIFILE_CloseCompressor(This);

	if (FAILED(IGetFrame_SetFormat(iface, &bi, NULL, 0, 0, -1, -1))) {
	  if (FAILED(IGetFrame_SetFormat(iface, NULL, NULL, 0, 0, -1, -1)))
	    return NULL;
	}
      } else if (FAILED(IGetFrame_SetFormat(iface, NULL, NULL, 0, 0, -1, -1)))
	return NULL;
    }
  }

  if (lPos != This->lCurrentFrame) {
    LONG lNext = IAVIStream_FindSample(This->pStream,lPos,FIND_KEY|FIND_PREV);

    if (lNext == -1)
      return NULL; /* frame doesn't exist */
    if (lNext <= This->lCurrentFrame && This->lCurrentFrame < lPos)
      lNext = This->lCurrentFrame + 1;

    for (; lNext <= lPos; lNext++) {
      /* new format for this frame? */
      if (This->bFormatChanges) {
	IAVIStream_ReadFormat(This->pStream, lNext,
			      This->lpInFormat, &This->cbInFormat);
	if (This->lpOutFormat != NULL) {
	  if (This->lpOutFormat->biBitCount <= 8)
	    ICDecompressGetPalette(This->hic, This->lpInFormat,
				   This->lpOutFormat);
	}
      }

      /* read input frame */
      while (FAILED(AVIStreamRead(This->pStream, lNext, 1, This->lpInBuffer,
				  This->cbInBuffer, &readBytes, &readSamples))) {
	/* not enough memory for input buffer? */
	readBytes = 0;
	if (FAILED(AVIStreamSampleSize(This->pStream, lNext, &readBytes)))
	  return NULL; /* bad thing, but bad things will happen */
	if (readBytes <= 0) {
	  ERR(": IAVIStream::Read doesn't return needed bytes!\n");
	  return NULL;
	}

	/* IAVIStream::Read failed because of other reasons not buffersize? */
	if (This->cbInBuffer >= readBytes)
	  break;
	This->cbInBuffer = This->cbInFormat + readBytes;
	This->lpInFormat = HeapReAlloc(GetProcessHeap(), 0, This->lpInFormat, This->cbInBuffer);
	if (This->lpInFormat == NULL)
	  return NULL; /* out of memory */
	This->lpInBuffer = (BYTE*)This->lpInFormat + This->cbInFormat;
      }

      if (readSamples != 1) {
	ERR(": no frames read\n");
	return NULL;
      }
      if (readBytes != 0) {
	This->lpInFormat->biSizeImage = readBytes;

	/* nothing to decompress? */
	if (This->hic == NULL) {
	  This->lCurrentFrame = lPos;
	  return This->lpInFormat;
	}

	if (This->bResize) {
	  ICDecompressEx(This->hic,0,This->lpInFormat,This->lpInBuffer,0,0,
			 This->lpInFormat->biWidth,This->lpInFormat->biHeight,
			 This->lpOutFormat,This->lpOutBuffer,This->x,This->y,
			 This->dx,This->dy);
	} else {
	  ICDecompress(This->hic, 0, This->lpInFormat, This->lpInBuffer,
		       This->lpOutFormat, This->lpOutBuffer);
	}
      }
    } /* for (lNext < lPos) */
  } /* if (This->lCurrentFrame != lPos) */

  return (This->hic == NULL ? This->lpInFormat : This->lpOutFormat);
}