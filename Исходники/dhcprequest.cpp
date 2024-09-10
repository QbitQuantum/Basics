/*
 * DetermineAdapter
 * 
 * NOTE:
 *   
 *    This code retrieves the Adapter Name to use for the DHCP Client API 
 *    using the IPHelper API.
 *   
 *    NT has a name for the adapter that through this API has device 
 *    information in front of it followed by a {GUID}, 98 does not and 
 *    the Index is used instead. So if the string is set to ?? (what it is 
 *    in 98) we revert to using the string representation of the index.
 *     
 */
LPSTR DetermineAdapter()
{
  DWORD dwResult;                            // result of API calls
  IP_INTERFACE_INFO * pInfo = NULL;          // adapter information structure
  DWORD dwSize = 0;                          // size of required buffer
  CHAR szAdapter[MAX_ADAPTER_NAME] = {0};    // the adapter to use 
  char * ptr;                                // pointer to adapter name

  // get buffer size
  dwResult = GetInterfaceInfo(NULL, &dwSize);     
  if (dwResult == ERROR_INSUFFICIENT_BUFFER)
    {
    // allocate buffer
    pInfo = (IP_INTERFACE_INFO *) LocalAlloc(LPTR, dwSize);
    if (!pInfo)
      {
      OutputError(GetLastError());
      exit(1);
      }

    // make the actual call
    dwResult = GetInterfaceInfo(pInfo, &dwSize);
    if (dwResult != ERROR_SUCCESS)
      {
      OutputError(GetLastError());
      exit(2);
      }
    }
  else
    {
    OutputError(GetLastError());
    exit(3);
    }
  
  // convert, parse, and convert back
  ptr = NULL;
  WideCharToMultiByte(0, 0, pInfo->Adapter[0].Name, 
                            lstrlenW(pInfo->Adapter[0].Name), 
                            szAdapter, MAX_ADAPTER_NAME, NULL, NULL);
  if (szAdapter[0] != '?')
    {
    // find the GUID
    ptr = strchr(szAdapter, '{'); 
    }

  // use index if the pointer is not set
  if (!ptr)
    {
    sprintf_s(szAdapter, MAX_ADAPTER_NAME, "%ld\0", pInfo->Adapter[0].Index);            
    ptr = szAdapter;
    }

  // free what was allocated
  if (pInfo)
    LocalFree(pInfo);

  return ptr;
}