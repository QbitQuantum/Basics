bool COMPort::Purge(DWORD dwFlags) {
  return PurgeComm((HANDLE(portHandle)), dwFlags);
}