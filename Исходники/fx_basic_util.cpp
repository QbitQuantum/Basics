void* FX_OpenFolder(const FX_WCHAR* path) {
#if _FXM_PLATFORM_ == _FXM_PLATFORM_WINDOWS_
  std::unique_ptr<CFindFileDataW> pData(new CFindFileDataW);
  pData->m_Handle = FindFirstFileExW((CFX_WideString(path) + L"/*.*").c_str(),
                                     FindExInfoStandard, &pData->m_FindData,
                                     FindExSearchNameMatch, nullptr, 0);
  if (pData->m_Handle == INVALID_HANDLE_VALUE)
    return nullptr;

  pData->m_bEnd = FALSE;
  return pData.release();
#else
  DIR* dir = opendir(CFX_ByteString::FromUnicode(path).c_str());
  return dir;
#endif
}