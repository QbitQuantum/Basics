unsigned __stdcall I4C3DAcceptedThreadProc(void* pParam)
{
    LoggingMessage(Log_Debug, _T(MESSAGE_DEBUG_PROCESSING), GetLastError(), g_FILE, __LINE__);

    I4C3DChildContext* pChildContext = (I4C3DChildContext*)pParam;

    I4C3DUDPPacket packet = {0};
    const SIZE_T packetBufferSize = sizeof(packet.szCommand);

    SIZE_T totalRecvBytes = 0;
    int nBytes = 0;
    BOOL bBreak = FALSE;

    DWORD dwResult = 0;
    WSAEVENT hEvent = NULL;
    WSAEVENT hEventArray[2] = {0};
    WSANETWORKEVENTS events = {0};

    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (hEvent == NULL) {
        LoggingMessage(Log_Error, _T(MESSAGE_ERROR_HANDLE_INVALID), GetLastError(), g_FILE, __LINE__);

        shutdown(pChildContext->clientSocket, SD_SEND);
        recv(pChildContext->clientSocket, packet.szCommand, packetBufferSize, 0);
        shutdown(pChildContext->clientSocket, SD_BOTH);
        closesocket(pChildContext->clientSocket);

        RemoveChildThread( pChildContext->hChildThread );
        free(pChildContext);
        return EXIT_FAILURE;
    }
    WSAEventSelect(pChildContext->clientSocket, hEvent, FD_READ | FD_CLOSE);

    hEventArray[0] = hEvent;
    hEventArray[1] = pChildContext->pContext->hStopEvent;

    FillMemory(packet.szCommand, packetBufferSize, 0xFF);
    while (!bBreak) {
        if (!CheckNetworkEventError(events)) {
            break;
        }

        dwResult = WSAWaitForMultipleEvents(2, hEventArray, FALSE, WSA_INFINITE, FALSE);

        DEBUG_PROFILE_MONITOR;

        if (dwResult == WSA_WAIT_FAILED) {
            LoggingMessage(Log_Error, _T(MESSAGE_ERROR_HANDLE_INVALID), GetLastError(), g_FILE, __LINE__);
            break;
        }

        if (dwResult - WSA_WAIT_EVENT_0 == 0) {
            if (WSAEnumNetworkEvents(pChildContext->clientSocket, hEvent, &events) != 0) {
                LoggingMessage(Log_Error, _T(MESSAGE_ERROR_HANDLE_INVALID), GetLastError(), g_FILE, __LINE__);
                break;
            }

            if (events.lNetworkEvents & FD_CLOSE) {
                break;

            } else if (events.lNetworkEvents & FD_READ) {
                nBytes = recv(pChildContext->clientSocket, packet.szCommand + totalRecvBytes, packetBufferSize - totalRecvBytes, 0);

                if (nBytes == SOCKET_ERROR) {
                    if (WSAGetLastError() == WSAEWOULDBLOCK) {
                        continue;
                    } else {
                        LoggingMessage(Log_Error, _T(MESSAGE_ERROR_SOCKET_RECV), WSAGetLastError(), g_FILE, __LINE__);
                    }
                    break;

                } else if (nBytes > 0) {

                    totalRecvBytes += nBytes;
                    PCSTR pTermination = (PCSTR)memchr(packet.szCommand, pChildContext->cTermination, totalRecvBytes);

                    // 終端文字が見つからない場合、バッファをクリア
                    if (pTermination == NULL) {
                        if (totalRecvBytes >= packetBufferSize) {
                            FillMemory(packet.szCommand, packetBufferSize, 0xFF);
                            totalRecvBytes = 0;
                        }
                        continue;
                    }

                    do {

                        DEBUG_PROFILE_MONITOR;

                        // プラグインへ電文転送
                        pChildContext->pContext->pController->Execute(&packet, pTermination-packet.szCommand+1);

                        volatile int i;
                        for (i = 0; i < g_sleepCount; ++i) {
                            Sleep(1);
                        }

                        //} else {
                        //	// Hotkey
                        //	MoveMemory(szCommand, recvBuffer, pTermination-recvBuffer);
                        //	szCommand[pTermination-recvBuffer] = '\0';
                        //	EnterCriticalSection(&g_Lock);
                        //	pChildContext->pContext->pController->Execute(pChildContext->pContext, &delta, szCommand);
                        //	LeaveCriticalSection(&g_Lock);
                        //}

                        if (pTermination == (packet.szCommand + totalRecvBytes - 1)) {
                            FillMemory(packet.szCommand, packetBufferSize, 0xFF);
                            totalRecvBytes = 0;

                        } else if (pTermination < (packet.szCommand + totalRecvBytes - 1)) {
                            int nCopySize = packetBufferSize - (pTermination - packet.szCommand + 1);

                            totalRecvBytes -= (pTermination - packet.szCommand + 1);
                            MoveMemory(packet.szCommand, pTermination+1, nCopySize);
                            FillMemory(packet.szCommand + nCopySize, packetBufferSize - nCopySize, 0xFF);

                        } else {
                            bBreak = TRUE;
                            LoggingMessage(Log_Error, _T(MESSAGE_ERROR_MESSAGE_INVALID), GetLastError(), g_FILE, __LINE__);
                            break;
                        }

                        DEBUG_PROFILE_MONITOR;

                    } while ((pTermination = (LPCSTR)memchr(packet.szCommand, pChildContext->cTermination, totalRecvBytes)) != NULL);

                    DEBUG_PROFILE_MONITOR;
                }

            }

        } else if (dwResult - WSA_WAIT_EVENT_0 == 1) {
            // pChildContext->pContext->hStopEvent に終了イベントがセットされた
            break;
        }

    }
    SafeCloseHandle(hEvent);

    // closesocket
    shutdown(pChildContext->clientSocket, SD_SEND);
    recv(pChildContext->clientSocket, packet.szCommand, packetBufferSize, 0);
    shutdown(pChildContext->clientSocket, SD_BOTH);
    closesocket(pChildContext->clientSocket);

    RemoveChildThread( pChildContext->hChildThread );
    free(pChildContext);

    LoggingMessage(Log_Debug, _T(MESSAGE_DEBUG_PROCESSING), GetLastError(), g_FILE, __LINE__);

    return EXIT_SUCCESS;
}