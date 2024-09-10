COMPILER_RT_VISIBILITY int lprofGetHostName(char *Name, int Len) {
  WCHAR Buffer[COMPILER_RT_MAX_HOSTLEN];
  DWORD BufferSize = sizeof(Buffer);
  BOOL Result =
      GetComputerNameExW(ComputerNameDnsFullyQualified, Buffer, &BufferSize);
  if (!Result)
    return -1;
  if (WideCharToMultiByte(CP_UTF8, 0, Buffer, -1, Name, Len, NULL, NULL) == 0)
    return -1;
  return 0;
}