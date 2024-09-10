LONG CRegistryKey::GetLastWriteTime(SYSTEMTIME &st)
{
	FILETIME ftLocal,ft;
	LONG nError = RegQueryInfoKeyW(m_hKey,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,&ft);

  if (nError == ERROR_SUCCESS)
  {
    FileTimeToLocalFileTime(&ft,&ftLocal);
    FileTimeToSystemTime(&ftLocal,&st);
  }

  return nError;
}