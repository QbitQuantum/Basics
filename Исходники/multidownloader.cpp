void ThreadProc(void* param)
{
    int index = (int)param;
    ICSE_OUTPUTDEBUGSTRING_W(L"[%d][%I64d:%I64d]", index, g_segmentMatrix[index][0], g_segmentMatrix[index][1]);
    __int64 begin = 0;
    __int64 end = g_segmentMatrix[index][0] - 1;
    __int64 backup = end;
    __int64 writeSize = 0LL;

LOOP:
    int iResult = 0;
    ADDRINFOW* result = NULL;
    ADDRINFOW* ptr = NULL;
    ADDRINFOW hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    WCHAR szDomain[MAX_URL_LENGTH] = {0};
    DWORD cchDecodeUrl = 0;
    CoInternetParseUrl(g_wcURL, PARSE_DOMAIN, 0, szDomain, MAX_URL_LENGTH, &cchDecodeUrl, 0);

    WCHAR* strProxyURL = L"test.proxy.com";
    WCHAR* strProxyPort = L"8080";
    iResult = GetAddrInfo(strProxyURL, strProxyPort, &hints, &result);
    if (iResult != 0)
    {
        ICSE_OUTPUTDEBUGSTRING_W(L"[%d]getaddrinfo failed: %d", index, iResult);
    }

    SOCKET connectSocket = INVALID_SOCKET;
    ptr = result;
    connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (connectSocket == INVALID_SOCKET)
    {
        ICSE_OUTPUTDEBUGSTRING_W(L"[%d]socket failed: %ld\n", index, WSAGetLastError());
        FreeAddrInfo(result);
    }

    int value = 0;
    int size = sizeof(value);
    iResult = getsockopt(connectSocket, SOL_SOCKET, SO_RCVBUF, (char*)&value, &size);

    iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    FreeAddrInfo(result);
    if (iResult == SOCKET_ERROR)
    {
        ICSE_OUTPUTDEBUGSTRING_W(L"[%d]connect failed: %d", index, iResult);
        closesocket(connectSocket);
    }

    do
    {
        begin = end + 1;
        end = ((begin + 32767) > g_segmentMatrix[index][1] ? g_segmentMatrix[index][1] : (begin + 32767));
        char sendBuff[DEFAULT_BUFFER_LENGTH] = {0};
        sprintf_s(sendBuff, DEFAULT_BUFFER_LENGTH,
            "GET %s HTTP/1.1\r\n" \
            "Host: %s\r\n" \
            "Proxy-Connection: keep-alive\r\n" \
            "Proxy-Authorization: Basic ***********\r\n" \
            "Accept: */*\r\n" \
            "Range: bytes=%I64d-%I64d\r\n"
            "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/44.0.2403.107 Safari/537.36\r\n\r\n",
            strstr(g_acURL, g_acDomain)+strlen(g_acDomain), g_acDomain, begin, end);
        iResult = send(connectSocket, sendBuff, (int)strlen(sendBuff), 0);
        if (iResult == SOCKET_ERROR)
        {
            ICSE_OUTPUTDEBUGSTRING_W(L"[%d]send failed: %d", index, WSAGetLastError());
            closesocket(connectSocket);
        }

        char recvBuff[DEFAULT_BUFFER_LENGTH * 33] = {0};
        int recvLength = 0;
        char* dataAddress = NULL;
        bool bRecvSucess = false;
        do
        {
            iResult = recv(connectSocket, recvBuff + recvLength, DEFAULT_BUFFER_LENGTH * 33 - recvLength, 0);
            if (iResult > 0)
            {
                recvLength += iResult;
                ICSE_OUTPUTDEBUGSTRING_W(L"[%d]recv length %d", index, iResult);
                dataAddress = StrStrA(recvBuff, "\r\n\r\n") + 4;
                if ((recvLength - (dataAddress - recvBuff)) == (int)(end - begin + 1))
                {
                    bRecvSucess = true;
                    break;
                }
            }
            else if (iResult == 0)
            {
                ICSE_OUTPUTDEBUGSTRING_W(L"[%d]Connection closed", index);
            }
            else
            {
                ICSE_OUTPUTDEBUGSTRING_W(L"[%d]recv failed %d", index, WSAGetLastError());
            }
        } while (iResult > 0);

        if (bRecvSucess)
        {
            HANDLE hFile = CreateFile(g_wcFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == NULL)
            {
                ICSE_OUTPUTDEBUGSTRING_W(L"[%d]file open failed %d", index, GetLastError());
                break;
            }
            LONG llow = (LONG)(begin & 0x0FFFFFFFF);
            LONG lhigh = (LONG)((begin & 0xFFFFFFFF00000000)>>32);
            DWORD dwPrt = SetFilePointer(hFile, llow, &lhigh, FILE_BEGIN);
            if (dwPrt == INVALID_SET_FILE_POINTER)
            {
                ICSE_OUTPUTDEBUGSTRING_W(L"[%d]move pointer failed %d", index, GetLastError());
                break;
            }
            DWORD dwSize = 0;
            WriteFile(hFile, dataAddress, (int)(end - begin + 1), &dwSize, NULL);
            CloseHandle(hFile);

            backup = end;
            writeSize += (__int64)dwSize;
            g_segmentMatrix[index][2] =writeSize;
            InvalidateRect(g_hWndMain, NULL, TRUE);
        }
        else
        {
            ICSE_OUTPUTDEBUGSTRING_W(L"[%d]recv error! %d", index, recvLength);
            closesocket(connectSocket);
            end = backup;
            goto LOOP;
        }
    } while (end < g_segmentMatrix[index][1]);