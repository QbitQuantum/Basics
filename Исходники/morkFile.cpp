void mork_fileflush(FILE * file)
{
  fflush(file);
#ifndef WINCE
  OSVERSIONINFOA vi = { sizeof(OSVERSIONINFOA) };
  if ((GetVersionExA(&vi) && vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS))
  {
    // Win9x/ME
    int fd = fileno(file);
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    FlushFileBuffers(fh);
  }
#endif
}