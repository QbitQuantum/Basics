bool SocketGetMacByIP(char *szIP, char *szMac)
{
	/*MIB_IPNETTABLE  IpNetTable;
	MIB_IPNETTABLE  *pIpNetTable = (MIB_IPNETTABLE *)malloc(246);
	DWORD   status   =   NO_ERROR;   
	//DWORD   statusRetry   =   NO_ERROR;   
	DWORD   dwActualSize   =   0;   
	          DWORD   i,   dwStatus,   dwCurrIndex;   
          struct   in_addr   inadTmp;   
          char   szPrintablePhysAddr[256];   
          char   szType[128];   
          char   szIpAddr[128];   
          PMIB_IPADDRTABLE   pIpAddrTable   =   NULL;   

	//   query   for   buffer   size   needed   
	dwActualSize   =   0;   
	status   =   GetIpNetTable(&IpNetTable,   &dwActualSize,  true);  
	if (status   ==   ERROR_INSUFFICIENT_BUFFER)   
	{   
		pIpNetTable   =   (PMIB_IPNETTABLE)   malloc(dwActualSize);   

		status   =   GetIpNetTable(pIpNetTable,   &dwActualSize,   true);   

		if   (status   !=   NO_ERROR)   
		{   
			return false; 
		}   
	}   
	if (status == NO_ERROR)
	{
		for   (i   =   0;   i   <   pIpNetTable->dwNumEntries;   ++i)   
          {    
          PhysAddrToString(pIpNetTable->table[i].bPhysAddr,   pIpNetTable->table[i].dwPhysAddrLen,   szPrintablePhysAddr);   
		  printf("mac :%s\n" , szPrintablePhysAddr);
		  }
	}
	return false;*/
	
	unsigned   char   macAddress[6]; 
	int i;
                  ULONG   macAddLen   =   6;   
                int  iRet=SendARP(inet_addr(szIP),   (unsigned   long)NULL,(PULONG)&macAddress,   &macAddLen); 
				if   (  iRet   ==   NO_ERROR   )   
                  {   
                          printf(   "MacAddress:   "   );   
                          for(     i   =0;   i<6;   i++   )   
                          {   
                                  printf(   "%.2x",   macAddress[i]   );   
                                  if   (   i<5   )   printf(   "-"   );   
                          }   
                          printf(   "\n"   );   
                  }   
else   
                          printf(   "SendARP   Error:%d\n",   GetLastError());   
                          //nRemoteAddr   =   htonl(   ntohl(   nRemoteAddr   )   +   1   );   

				return true;

}