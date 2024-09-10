int GetIFCDetails(char *pIFCName, PSCANPARAMS pScanParams)
{
  int lRetVal = 0;
  unsigned long lLocalIPAddr = 0;
  unsigned long lGWIPAddr = 0;
  ULONG lGWMACAddr[2];
  ULONG lGWMACAddrLen = 6;
  PIP_ADAPTER_INFO lAdapterInfoPtr = NULL;
  PIP_ADAPTER_INFO lAdapter = NULL;
  DWORD lFuncRetVal = 0;
  ULONG lOutBufLen = sizeof (IP_ADAPTER_INFO);


  if ((lAdapterInfoPtr = (IP_ADAPTER_INFO *) HeapAlloc(GetProcessHeap(), 0, sizeof (IP_ADAPTER_INFO))) == NULL)
  {
    LogMsg("getIFCDetails() : Error allocating memory needed to call GetAdaptersinfo\n");
    lRetVal = 1;
    goto END;
  } // if ((lAdapterInfo...


  if (GetAdaptersInfo(lAdapterInfoPtr, &lOutBufLen) == ERROR_BUFFER_OVERFLOW) 
  {
    HeapFree(GetProcessHeap(), 0, lAdapterInfoPtr);
    if ((lAdapterInfoPtr = (IP_ADAPTER_INFO *) HeapAlloc(GetProcessHeap(), 0, lOutBufLen)) == NULL)
    {
      LogMsg("getIFCDetails() : Error allocating memory needed to call GetAdaptersinfo");
      lRetVal = 2;
      goto END;
    } // if ((lAdap...
  } // if (GetAdapte...



  /*
   *
   *
   */
  if ((lFuncRetVal = GetAdaptersInfo(lAdapterInfoPtr, &lOutBufLen)) == NO_ERROR) 
  {
    for (lAdapter = lAdapterInfoPtr; lAdapter; lAdapter = lAdapter->Next)
    {
      if (StrStrI(pIFCName, lAdapter->AdapterName))
	     {
        // Get local MAC address
        CopyMemory(pScanParams->LocalMAC, lAdapter->Address, BIN_MAC_LEN);

        // Get local IP address
        lLocalIPAddr = inet_addr(lAdapter->IpAddressList.IpAddress.String);
        CopyMemory(pScanParams->LocalIP, &lLocalIPAddr, 4);


      		// Get gateway IP address
        lGWIPAddr = inet_addr(lAdapter->GatewayList.IpAddress.String);
        CopyMemory(pScanParams->GWIP, &lGWIPAddr, 4);


        // Get gateway MAC address
        CopyMemory(pScanParams->GWIP, &lGWIPAddr, 4); // ????
        ZeroMemory(&lGWMACAddr, sizeof(lGWMACAddr));
        SendARP(lGWIPAddr, 0, lGWMACAddr, &lGWMACAddrLen);
        CopyMemory(pScanParams->GWMAC, lGWMACAddr, 6);

		      // Get interface index.
		      pScanParams->Index = lAdapter->Index;

		      // Get interface description
		      CopyMemory(pScanParams->IFCDescr, lAdapter->Description, sizeof(pScanParams->IFCDescr) - 1);

        break;
	     } // if (StrSt...
    } // for (lAdapt...


  }
  else
  {
    lRetVal = 1;
  } // if ((lFunc...

END:
  if (lAdapterInfoPtr)
    HeapFree(GetProcessHeap(), 0, lAdapterInfoPtr);


  return(lRetVal);
}