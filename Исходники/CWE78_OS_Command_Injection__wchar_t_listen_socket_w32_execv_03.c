void CWE78_OS_Command_Injection__wchar_t_listen_socket_w32_execv_03_bad()
{
    wchar_t * data;
    wchar_t dataBuffer[100] = L"";
    data = dataBuffer;
    if(5==5)
    {
        {
#ifdef _WIN32
            WSADATA wsaData;
            int wsaDataInit = 0;
#endif
            int recvResult;
            struct sockaddr_in service;
            wchar_t *replace;
            SOCKET listenSocket = INVALID_SOCKET;
            SOCKET acceptSocket = INVALID_SOCKET;
            size_t dataLen = wcslen(data);
            do
            {
#ifdef _WIN32
                if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
                {
                    break;
                }
                wsaDataInit = 1;
#endif
                /* POTENTIAL FLAW: Read data using a listen socket */
                listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                if (listenSocket == INVALID_SOCKET)
                {
                    break;
                }
                memset(&service, 0, sizeof(service));
                service.sin_family = AF_INET;
                service.sin_addr.s_addr = INADDR_ANY;
                service.sin_port = htons(TCP_PORT);
                if (bind(listenSocket, (struct sockaddr*)&service, sizeof(service)) == SOCKET_ERROR)
                {
                    break;
                }
                if (listen(listenSocket, LISTEN_BACKLOG) == SOCKET_ERROR)
                {
                    break;
                }
                acceptSocket = accept(listenSocket, NULL, NULL);
                if (acceptSocket == SOCKET_ERROR)
                {
                    break;
                }
                /* Abort on error or the connection was closed */
                recvResult = recv(acceptSocket, (char *)(data + dataLen), sizeof(wchar_t) * (100 - dataLen - 1), 0);
                if (recvResult == SOCKET_ERROR || recvResult == 0)
                {
                    break;
                }
                /* Append null terminator */
                data[dataLen + recvResult / sizeof(wchar_t)] = L'\0';
                /* Eliminate CRLF */
                replace = wcschr(data, L'\r');
                if (replace)
                {
                    *replace = L'\0';
                }
                replace = wcschr(data, L'\n');
                if (replace)
                {
                    *replace = L'\0';
                }
            }
            while (0);
            if (listenSocket != INVALID_SOCKET)
            {
                CLOSE_SOCKET(listenSocket);
            }
            if (acceptSocket != INVALID_SOCKET)
            {
                CLOSE_SOCKET(acceptSocket);
            }
#ifdef _WIN32
            if (wsaDataInit)
            {
                WSACleanup();
            }
#endif
        }
    }
    {
        wchar_t *args[] = {COMMAND_INT_PATH, COMMAND_ARG1, COMMAND_ARG2, COMMAND_ARG3, NULL};
        /* wexecv - specify the path where the command is located */
        /* POTENTIAL FLAW: Execute command without validating input possibly leading to command injection */
        EXECV(COMMAND_INT_PATH, args);
    }
}