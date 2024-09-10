HRESULT VegasFSRender::writeData(ISfProgress* progress) {
  BOOL useAudio = (m_pIAudioStream &&
                   m_pTemplate->pAudioTemplate &&
                   m_pTemplate->pAudioTemplate->cNumAStreams);
  BOOL useVideo = (m_pIVideoStream &&
                   m_pTemplate->pVideoTemplate &&
                   m_pTemplate->pVideoTemplate->cNumVStreams);

  if (!useVideo)
    return SF_E_NOVIDEO;

  HWND activewnd = GetForegroundWindow();
  DWORD threadid = GetWindowThreadProcessId(activewnd, NULL);
  AttachThreadInput(GetCurrentThreadId(), threadid, TRUE);

  ZeroMemory(&FfpHeader, NUMBYTES(FfpHeader));

  LPTSTR pszFileName;
#ifdef UNICODE
  pszFileName = m_szFileName;
#else
  TCHAR szFileName[MAX_PATH];
  SfMBFromWC(szFileName, m_szFileName, MAX_PATH);
  pszFileName = szFileName;
#endif
  HRESULT hr = S_OK;

  hr = m_pIVideoStream->GetFrameCount(&FfpHeader.Video.cfTotal);
  hr = m_pIVideoStream->GetFrameRate(&FfpHeader.Video.dFPS);
  FfpHeader.Video.ntLength = SfVideo_FramesToTime(
      FfpHeader.Video.cfTotal, FfpHeader.Video.dFPS);
  FfpHeader.Video.bih = *m_pTemplate->pVideoTemplate->pbihCodec;
  FfpHeader.Video.cbFrameSize = FSDibImageBytes(&FfpHeader.Video.bih);
  if (useAudio) {
    hr = m_pIAudioStream->GetSampleCount(&FfpHeader.Audio.ccTotal);
    FfpHeader.Audio.wfx = m_pTemplate->pAudioTemplate->wfx;
    hr = m_pIAudioStream->GetStreamLength(&FfpHeader.Audio.ntLength);
    FfpHeader.Audio.ntLength = SfAudio_CellsToTime(FfpHeader.Audio.ccTotal,
        FfpHeader.Audio.wfx.nSamplesPerSec);
  }

  Init(!!useAudio, FfpHeader.Audio.wfx.nSamplesPerSec,
      FfpHeader.Audio.wfx.wBitsPerSample, FfpHeader.Audio.wfx.nChannels,
      (DWORD)FfpHeader.Video.cfTotal, FfpHeader.Video.dFPS,
      FfpHeader.Video.bih.biWidth, FfpHeader.Video.bih.biHeight, activewnd, pszFileName);
  hr = S_OK;
  if (!Run())
    hr = SF_E_CANCEL;

  EnableWindow(activewnd, TRUE);
  SetForegroundWindow(activewnd);
  AttachThreadInput(GetCurrentThreadId(), threadid, FALSE);
  return hr;
}