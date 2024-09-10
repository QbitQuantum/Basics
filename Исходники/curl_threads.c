/* !checksrc! disable SPACEBEFOREPAREN 1 */
curl_thread_t Curl_thread_create(unsigned int (CURL_STDCALL *func) (void *),
                                 void *arg)
{
  curl_thread_t t;
#ifdef _WIN32_WCE
  t = CreateThread(NULL, 0, func, arg, 0, NULL);
#else
  uintptr_t thread_handle = _beginthreadex(NULL, 0, func, arg, 0, NULL);
  t = (curl_thread_t)thread_handle;
#endif
  if((t == 0) || (t == LongToHandle(-1L))) {
#ifdef _WIN32_WCE
    DWORD gle = GetLastError();
    errno = ((gle == ERROR_ACCESS_DENIED ||
              gle == ERROR_NOT_ENOUGH_MEMORY) ?
             EACCES : EINVAL);
#endif
    return curl_thread_t_null;
  }
  return t;
}