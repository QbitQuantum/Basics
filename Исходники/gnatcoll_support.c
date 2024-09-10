int
__gnatcoll_get_logical_drive_strings (char *buffer, int len)
{
#ifdef _WIN32
  return GetLogicalDriveStringsA ((DWORD)len, (LPSTR)buffer);
#else
  return 0;
#endif
}