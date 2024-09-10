/**
 * Flushes the file buffers, writing all data immediately.
 * @return Returns 1 on success, 0 on error.
*/
short LbFileFlush(TbFileHandle handle)
{
#if defined(WIN32)
  int result;
  // Crappy Windows has its own
  result = FlushFileBuffers((HANDLE)handle);
  // It returns 'invalid handle' error sometimes for no reason.. so disabling this error
  if (result != 0)
      return 1;
  result = GetLastError();
  return ((result == 0) || (result == 6));
#else
#if defined(DOS)||defined(GO32)
  // No idea how to do this on old systems
  return 1;
#else
  // For normal POSIX systems
  // (should also work on Win, as its IEEE standard... but it currently isn't)
  return (ioctl(handle,I_FLUSH,FLUSHRW) != -1);
#endif
#endif

}