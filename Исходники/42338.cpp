int main() {
  HMODULE hNsi = LoadLibraryW(L"Nsi.dll");
  NsiGetParameterProc _NsiGetParameter = (NsiGetParameterProc)GetProcAddress(hNsi, "NsiGetParameter");

  // Declare and initialize variables
  PIP_INTERFACE_INFO pInfo = NULL;
  ULONG ulOutBufLen = 0;

  DWORD dwRetVal = 0;
  int iReturn = 1;

  int i;

  // Make an initial call to GetInterfaceInfo to get
  // the necessary size in the ulOutBufLen variable
  dwRetVal = GetInterfaceInfo(NULL, &ulOutBufLen);
  if (dwRetVal == ERROR_INSUFFICIENT_BUFFER) {
    pInfo = (IP_INTERFACE_INFO *)MALLOC(ulOutBufLen);
    if (pInfo == NULL) {
      printf
        ("Unable to allocate memory needed to call GetInterfaceInfo\n");
      return 1;
    }
  }
  // Make a second call to GetInterfaceInfo to get
  // the actual data we need
  dwRetVal = GetInterfaceInfo(pInfo, &ulOutBufLen);
  if (dwRetVal == NO_ERROR) {
    printf("Number of Adapters: %ld\n\n", pInfo->NumAdapters);
    for (i = 0; i < pInfo->NumAdapters; i++) {
      printf("Adapter Index[%d]: %ld\n", i,
        pInfo->Adapter[i].Index);

      NET_LUID Luid;
      NETIO_STATUS st = ConvertInterfaceIndexToLuid(pInfo->Adapter[i].Index, &Luid);
      if (st == NO_ERROR) {
        BYTE OutputBuffer[0xB8] = { /* zero padding */ };
        DWORD nsi_st = _NsiGetParameter(1, NPI_MS_IPV4_MODULEID, 7, &Luid, sizeof(Luid), 0, OutputBuffer, sizeof(OutputBuffer), 0);
        if (nsi_st == NO_ERROR) {
          PrintHex(OutputBuffer, sizeof(OutputBuffer));
        }
      }
    }
    iReturn = 0;
  }
  else if (dwRetVal == ERROR_NO_DATA) {
    printf
      ("There are no network adapters with IPv4 enabled on the local system\n");
    iReturn = 0;
  }
  else {
    printf("GetInterfaceInfo failed with error: %d\n", dwRetVal);
    iReturn = 1;
  }

  FREE(pInfo);
  return (iReturn);
}