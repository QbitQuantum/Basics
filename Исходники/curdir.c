/*
 * @unimplemented
 */
UINT
WINAPI
GetSystemWow64DirectoryA(
    LPSTR lpBuffer,
    UINT uSize
    )
{
#ifdef _WIN64
   WCHAR BufferW[MAX_PATH];
   UINT ret;

   ret = GetSystemWow64DirectoryW(BufferW, MAX_PATH);

   if (!ret) return 0;
   if (ret > MAX_PATH)
   {
      SetLastError(ERROR_FILENAME_EXCED_RANGE);
      return 0;
   }

   return FilenameW2A_FitOrFail(lpBuffer, uSize, BufferW, ret+1);
#else
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return 0;
#endif
}