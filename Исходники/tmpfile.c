PAVIFILE AVIFILE_CreateAVITempFile(int nStreams, const PAVISTREAM *ppStreams)
{
  ITmpFileImpl *tmpFile;
  int           i;

  tmpFile = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(ITmpFileImpl));
  if (tmpFile == NULL)
    return NULL;

  tmpFile->IAVIFile_iface.lpVtbl = &itmpft;
  tmpFile->ref    = 1;
  memset(&tmpFile->fInfo, 0, sizeof(tmpFile->fInfo));

  tmpFile->fInfo.dwStreams = nStreams;
  tmpFile->ppStreams = HeapAlloc(GetProcessHeap(), 0, nStreams * sizeof(PAVISTREAM));
  if (tmpFile->ppStreams == NULL) {
    HeapFree(GetProcessHeap(), 0, tmpFile);
    return NULL;
  }

  for (i = 0; i < nStreams; i++) {
    AVISTREAMINFOW sInfo;

    tmpFile->ppStreams[i] = ppStreams[i];

    AVIStreamAddRef(ppStreams[i]);
    AVIStreamInfoW(ppStreams[i], &sInfo, sizeof(sInfo));
    if (i == 0) {
      tmpFile->fInfo.dwScale = sInfo.dwScale;
      tmpFile->fInfo.dwRate  = sInfo.dwRate;
      if (!sInfo.dwScale || !sInfo.dwRate) {
        tmpFile->fInfo.dwScale = 1;
        tmpFile->fInfo.dwRate  = 100;
      }
    }

    if (tmpFile->fInfo.dwSuggestedBufferSize < sInfo.dwSuggestedBufferSize)
      tmpFile->fInfo.dwSuggestedBufferSize = sInfo.dwSuggestedBufferSize;

    {
      DWORD tmp;

      tmp = MulDiv(AVIStreamSampleToTime(ppStreams[i], sInfo.dwLength),
                   tmpFile->fInfo.dwScale, tmpFile->fInfo.dwRate * 1000);
      if (tmpFile->fInfo.dwLength < tmp)
        tmpFile->fInfo.dwLength = tmp;

      tmp = sInfo.rcFrame.right - sInfo.rcFrame.left;
      if (tmpFile->fInfo.dwWidth < tmp)
        tmpFile->fInfo.dwWidth = tmp;
      tmp = sInfo.rcFrame.bottom - sInfo.rcFrame.top;
      if (tmpFile->fInfo.dwHeight < tmp)
        tmpFile->fInfo.dwHeight = tmp;
    }
  }

  return &tmpFile->IAVIFile_iface;
}