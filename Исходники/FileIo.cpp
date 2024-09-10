bool COutFile::SetTime(const FILETIME *lpCreationTime,
  const FILETIME *lpLastAccessTime, const FILETIME *lpLastWriteTime)
{
  LARGE_INTEGER  ltime;
  DWORD dw;

  if (_fd == -1) {
     SetLastError( ERROR_INVALID_HANDLE );
     return false;
  }

  /* On some OS (cygwin, MacOSX ...), you must close the file before updating times */
  if (lpLastAccessTime) {
     ltime.QuadPart = lpLastAccessTime->dwHighDateTime;
     ltime.QuadPart = (ltime.QuadPart << 32) | lpLastAccessTime->dwLowDateTime;
     RtlTimeToSecondsSince1970( &ltime, &dw );
     _lastAccessTime = dw;
  }
  if (lpLastWriteTime) {
     ltime.QuadPart = lpLastWriteTime->dwHighDateTime;
     ltime.QuadPart = (ltime.QuadPart << 32) | lpLastWriteTime->dwLowDateTime;
     RtlTimeToSecondsSince1970( &ltime, &dw );
     _lastWriteTime = dw;
  }

  return true;
}