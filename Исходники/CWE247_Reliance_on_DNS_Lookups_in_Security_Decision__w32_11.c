/* good2() reverses the bodies in the if statement */
static void good2()
{
    if(globalReturnsTrue())
    {
        {
            WSADATA wsaData;
            BOOL wsaDataInit = FALSE;
            SOCKET listenSocket = INVALID_SOCKET;
            SOCKET client = INVALID_SOCKET;
            struct sockaddr_in service;
            struct sockaddr_in serviceClient;
            int serviceClientLen;
            struct hostent *hostInfo;
            FILE * pFile;
            do
            {
                if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
                {
                    break;
                }
                wsaDataInit = TRUE;
                listenSocket = socket(PF_INET, SOCK_STREAM, 0);
                if (listenSocket == INVALID_SOCKET)
                {
                    break;
                }
                memset(&service, 0, sizeof(service));
                service.sin_family = AF_INET;
                service.sin_addr.s_addr = INADDR_ANY;
                service.sin_port = htons(LISTEN_PORT);
                if (SOCKET_ERROR == bind(listenSocket, (struct sockaddr*)&service, sizeof(service)))
                {
                    break;
                }
                if (SOCKET_ERROR == listen(listenSocket, LISTEN_BACKLOG))
                {
                    break;
                }
                serviceClientLen = sizeof(serviceClient);
                client = accept(listenSocket, (struct sockaddr*)&serviceClient, &serviceClientLen);
                if (client == INVALID_SOCKET)
                {
                    break;
                }
                if (serviceClient.sin_family != AF_INET)
                {
                    break;
                }
                hostInfo = gethostbyaddr((char*)&serviceClient.sin_addr, sizeof(serviceClient.sin_addr), AF_INET);
                if (hostInfo == NULL)
                {
                    break;
                }
                if (hostInfo->h_name == NULL)
                {
                    break;
                }
                printLine(hostInfo->h_name);
                /* FIX: Copy the host name to a log - do not attempt to use the host name in a security decision */
                pFile = fopen("log.txt", "a+");
                fprintf(pFile, "Host name: %s\n", hostInfo->h_name);
                fclose(pFile);
            }
            while (0);
            if (client != INVALID_SOCKET)
            {
                closesocket(client);
            }
            if (listenSocket != INVALID_SOCKET)
            {
                closesocket(listenSocket);
            }
            if (wsaDataInit)
            {
                WSACleanup();
            }
        }
    }
}