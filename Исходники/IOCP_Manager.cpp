bool IOCP_Manager::Initialize()
{
    SYSTEM_INFO SystemInfo;
    GetSystemInfo(&SystemInfo);
    mIoThreadCount = SystemInfo.dwNumberOfProcessors * 2;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf_s("WSAStartup Error\n");
        return false;
    }

    mCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, mIoThreadCount);
    if (mCompletionPort == NULL)
    {
        printf_s("Create CompletionPort error\n");
        return false;
    }

    mListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);
    if (mListenSocket == INVALID_SOCKET)
    {
        printf_s("Create ListenSocket Error\n");
        return false;
    }

    int opt = 1;
    setsockopt(mListenSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(int));

    SOCKADDR_IN ServerAddr;
    int SizeServerAddr = sizeof(SOCKADDR_IN);
    memset(&ServerAddr, 0, SizeServerAddr);
    if (WSAStringToAddress(L"127.0.0.1:9001", AF_INET, NULL, (SOCKADDR*)&ServerAddr, &SizeServerAddr) == SOCKET_ERROR)
    {
        printf_s("ServerAddress Setting Error\n");
        return false;
    }

    if (bind(mListenSocket, (SOCKADDR*)&ServerAddr, SizeServerAddr) == SOCKET_ERROR)
    {
        printf_s("Bind Error\n");
        return false;
    }

    return true;
}