HANDLE
XCECreateMutexW(LPSECURITY_ATTRIBUTES sa, BOOL io, LPTSTR name)
{
  HANDLE hnd;

  hnd = CreateMutexW(sa, io, name);
  WCETRACE(WCE_SYNCH, "cmw: %p", hnd);
  return(hnd);
}