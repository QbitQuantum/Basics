BOOL XCEAPI
XCECreateDirectoryW(const wchar_t *oldpath, LPSECURITY_ATTRIBUTES lpSec)
{
  wchar_t newpath[MAX_PATH];

  XCEFixPathW(oldpath, newpath);
  return CreateDirectoryW(newpath, lpSec);
}