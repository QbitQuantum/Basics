HRESULT CLAVAudio::InitDTSDecoder()
{
  if (!m_hDllExtraDecoder) {
    // Add path of LAVAudio.ax into the Dll search path
    WCHAR wModuleFile[1024];
    GetModuleFileName(g_hInst, wModuleFile, 1024);
    PathRemoveFileSpecW(wModuleFile);
    wcscat_s(wModuleFile, TEXT("\\dtsdecoderdll.dll"));

    // Try loading from the filters directory
    HMODULE hDll = LoadLibraryEx(wModuleFile, nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
    // And try from any global directories if this failed
    if (hDll == nullptr) {
      hDll = LoadLibrary(TEXT("dtsdecoderdll.dll"));
    }
    CheckPointer(hDll, E_FAIL);

    BOOL bIncompatibleDecoder = FALSE;
    if (GetModuleFileName(hDll, wModuleFile, 1024) > 0) {
      DWORD dwVersionSize = GetFileVersionInfoSize(wModuleFile, nullptr);
      if (dwVersionSize > 0) {
        void *versionInfo = CoTaskMemAlloc(dwVersionSize);
        BOOL bVersionInfoPresent = GetFileVersionInfo(wModuleFile, 0, dwVersionSize, versionInfo);
        if (bVersionInfoPresent) {
          VS_FIXEDFILEINFO *info;
          unsigned cbInfo;
          BOOL bInfoPresent = VerQueryValue(versionInfo, TEXT("\\"), (LPVOID*)&info, &cbInfo);
          if (bInfoPresent) {
            bInfoPresent = bInfoPresent;
            uint64_t version = info->dwFileVersionMS;
            version <<= 32;
            version += info->dwFileVersionLS;
            if (version && version < 0x0001000100000000i64)
              bIncompatibleDecoder = TRUE;
          }
        }
        CoTaskMemFree(versionInfo);
      }

    }

    if (bIncompatibleDecoder) {
      FreeLibrary(hDll);
      hDll = nullptr;
      return E_FAIL;
    }

    m_hDllExtraDecoder = hDll;
  }

  DTSDecoder *context = new DTSDecoder();

  context->pDtsOpen = (DtsOpen)GetProcAddress(m_hDllExtraDecoder, "DtsApiDecOpen");
  if(!context->pDtsOpen) goto fail;

  context->pDtsClose = (DtsClose)GetProcAddress(m_hDllExtraDecoder, "DtsApiDecClose");
  if(!context->pDtsClose) goto fail;

  context->pDtsReset = (DtsReset)GetProcAddress(m_hDllExtraDecoder, "DtsApiDecReset");
  if(!context->pDtsReset) goto fail;

  context->pDtsSetParam = (DtsSetParam)GetProcAddress(m_hDllExtraDecoder, "DtsApiDecSetParam");
  if(!context->pDtsSetParam) goto fail;

  context->pDtsDecode = (DtsDecode)GetProcAddress(m_hDllExtraDecoder, "DtsApiDecodeData");
  if(!context->pDtsDecode) goto fail;

  context->dtsContext = context->pDtsOpen();
  if(!context->dtsContext) goto fail;

  context->dtsPCMBuffer = (BYTE *)av_mallocz(LAV_AUDIO_BUFFER_SIZE + FF_INPUT_BUFFER_PADDING_SIZE);

  m_DTSBitDepth = 24;
  m_DTSDecodeChannels = 8;

  m_pDTSDecoderContext = context;

  FlushDTSDecoder();

  return S_OK;
fail:
  SAFE_DELETE(context);
  FreeLibrary(m_hDllExtraDecoder);
  m_hDllExtraDecoder = nullptr;
  return E_FAIL;
}