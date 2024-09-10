bool Win32DllLoader::Load()
{
  if (m_dllHandle != NULL)
    return true;

  CStdString strFileName = GetFileName();
  CLog::Log(LOGDEBUG, "%s(%s)\n", __FUNCTION__, strFileName.c_str());

  CStdStringW strDllW;
  g_charsetConverter.utf8ToW(_P(strFileName), strDllW);
  m_dllHandle = LoadLibraryExW(strDllW.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
  if (!m_dllHandle)
  {
    CLog::Log(LOGERROR, "%s: Unable to load %s (%d)", __FUNCTION__, strFileName.c_str(), GetLastError());
    return false;
  }

  // handle functions that the dll imports
  if (NeedsHooking(strFileName.c_str()))
    OverrideImports(strFileName);
  else
    bIsSystemDll = true;

  return true;
}