/*
 * Clear the HANDLE_FLAG_INHERIT flag from all HANDLEs that were inherited
 * the parent process. Don't check for errors - the stdio handles may not be
 * valid, or may be closed already. There is no guarantee that this function
 * does a perfect job.
 */
void uv_disable_stdio_inheritance(void) {
  HANDLE handle;
  STARTUPINFOW si;

  /* Make the windows stdio handles non-inheritable. */
  handle = GetStdHandle(STD_INPUT_HANDLE);
  if (handle != NULL && handle != INVALID_HANDLE_VALUE)
    SetHandleInformation(handle, HANDLE_FLAG_INHERIT, 0);

  handle = GetStdHandle(STD_OUTPUT_HANDLE);
  if (handle != NULL && handle != INVALID_HANDLE_VALUE)
    SetHandleInformation(handle, HANDLE_FLAG_INHERIT, 0);

  handle = GetStdHandle(STD_ERROR_HANDLE);
  if (handle != NULL && handle != INVALID_HANDLE_VALUE)
    SetHandleInformation(handle, HANDLE_FLAG_INHERIT, 0);

  /* Make inherited CRT FDs non-inheritable. */
  GetStartupInfoW(&si);
  if (uv__stdio_verify(si.lpReserved2, si.cbReserved2))
    uv__stdio_noinherit(si.lpReserved2);
}