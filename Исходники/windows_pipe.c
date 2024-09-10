DWORD WINAPI
rx_thread(void *lpParameter_)
{
    DWORD dwWaitResult, e;
    char rx_pipe_name[32];
    BOOL b, bReadFail;

    for (;;) {
        int nbytes;
        DWORD NumberOfBytesRead;
        //printf("rx_thread waiting for rx start...\n");
        dbg_rx_state = RS__WAITING_FOR_RXSTART;
    
        dwWaitResult = WaitForSingleObject(ghRxStartEvent, INFINITE);
        if (dwWaitResult != WAIT_OBJECT_0) {
            printf("[41mghRxStartEvent wait fail %ld, %ld[0m\n", dwWaitResult, GetLastError());
            Sleep(50);
            continue;
        }

        //printf("rx_thread notified\n");
        ResetEvent(ghRxStartEvent);

        if (g_timeout_ms == 0) {
            /* some events on the pipe might cause spurious event */
            //printf("rx_thread: zero timeout\n");
            radio_pipe_close();
            continue;
        }

        sprintf(rx_pipe_name, "%s%02x", pipe_name_prefix, gsid);
create_pipe:
        ghRxPipe = CreateNamedPipe(
            /*LPCTSTR lpName*/rx_pipe_name,
            /*DWORD dwOpenMode*/PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
            /*DWORD dwPipeMode*/PIPE_TYPE_MESSAGE,
            /*DWORD nMaxInstances*/1,  // XXX each receiver on its own pipe XXX
            /*DWORD nOutBufferSize*/0,
            /*DWORD nInBufferSize*/632,
            /*DWORD nDefaultTimeOut*/g_timeout_ms,
            /*LPSECURITY_ATTRIBUTES lpSecurityAttributes*/NULL
        );
        if (ghRxPipe == INVALID_HANDLE_VALUE) {
            e = GetLastError();
            ghRxPipe = NULL;
            if (e == ERROR_PIPE_BUSY) {
                //printf("CreateNamedPipe(): somebody else already receiving  %d\n", g_timeout_ms);
                if (g_timeout_ms > 20) {
                    g_timeout_ms -= 20;
                    Sleep(20);
                    goto create_pipe;
                }
            } else {
                if (e == ERROR_INVALID_HANDLE) {
                    printf("[41mCreateNamedPipe(): ERROR_INVALID_HANDLE[0m\n");
                } else {
                    printf("[41mCreateNamedPipe(): %ld[0m\n", e);
                }
                radio.evtdone(RM2_ERR_GENERIC, 0);
                g_timeout_ms = 0;
            }
            continue;
        }

        // create manual reset event object
        goConnect.hEvent = CreateEvent(
            /*LPSECURITY_ATTRIBUTES lpEventAttributes*/NULL,
            /*BOOL bManualReset*/TRUE,
            /*BOOL bInitialState*/FALSE,
            /*LPCTSTR lpName*/"foo"
        );
        if (goConnect.hEvent == NULL) {
            printf("CreateEvent() %ld\n", GetLastError());
            break;
        }

        b = ConnectNamedPipe(
            /*HANDLE hNamedPipe*/ghRxPipe,
            /*LPOVERLAPPED lpOverlapped*/&goConnect
        );
        if (b != 0) {
            printf("%d = ConnectNamedPipe()\n", b); // unexpected
            break;
        }

#ifdef RADIO_DEBUG
        printf("rx_thread wait %d for connect %s\n", g_timeout_ms, rx_pipe_name);
#endif
        dbg_rx_state = RS__WAITING_FOR_CONNECT;
        dwWaitResult = WaitForSingleObject(goConnect.hEvent, g_timeout_ms);
        if (dwWaitResult == WAIT_TIMEOUT) {
            /* nobody transmitted within timeout period */
#ifdef RADIO_DEBUG
            printf("rx_thread ConnectNamedPipe() WAIT_TIMEOUT\n");
#endif
            radio_pipe_close();
            continue;
        } else if (dwWaitResult != WAIT_OBJECT_0) {
            printf("[41mconnect wait failed %ld[0m\n", GetLastError());
            radio_pipe_close();
            continue;
        }

        /* transmitting side has connected */

        bReadFail = FALSE;
        nbytes = em2_remaining_bytes();
        do { // while (nbytes > 0)...
            if (nbytes > (RX_BUF_SIZE-1))
                nbytes = (RX_BUF_SIZE-1);

            dbg_rx_state = RS__READFILE;
            /* this read is blocking: we're in our own thread */
            b = ReadFile(
                /*HANDLE hFile*/ghRxPipe,
                /*LPVOID lpBuffer*/&rx_buf,
                /*DWORD nNumberOfBytesToRead*/nbytes,
                /*LPDWORD lpNumberOfBytesRead*/&NumberOfBytesRead,
                /*LPOVERLAPPED lpOverlapped*/&goConnect
            );

            if (b == 0) {
                DWORD nbt;
                DWORD e = GetLastError();
                if (e == ERROR_PIPE_LISTENING) {
                    bReadFail = TRUE;
                    printf("ReadFile(): write side disconnected[0m\n");
                    radio_pipe_close();
                    break;
                } else if (e == ERROR_IO_PENDING) {
                    /* read operation is completing asynchronously */
                    b = GetOverlappedResult(
                        /*HANDLE hFile*/ghRxPipe,
                        /*LPOVERLAPPED lpOverlapped*/&goConnect,
                        /*LPDWORD lpNumberOfBytesTransferred*/&nbt,
                        /*BOOL bWait*/TRUE /* blocking */
                    );
                    if (b) {
                        rx_buf_in_idx = nbt;
                    } else {
                        e = GetLastError();
                        printf("[41mGetOverlappedResult() failed %ld[0m\n", e);
                        radio_pipe_close();
                        bReadFail = TRUE;
                        break;
                    }
                } else {
                    if (e == ERROR_INVALID_HANDLE) {
                        /* this likely occurs because rx pipe was closed */
                        printf("[41mReadFile() ERROR_INVALID_HANDLE[0m\n");
                        radio_pipe_close();
                        bReadFail = TRUE;
                        break;
                    } else {
                        printf("[41mReadFile() failed %ld[0m\n", e);
                        radio_pipe_close();
                        bReadFail = TRUE;
                        break;
                    }
                }
            } else {
                // read operation completed synchronously
                rx_buf_in_idx = NumberOfBytesRead;
            }

            rx_buf_out_idx = 0;
            em2_decode_data();

            nbytes = em2_remaining_bytes();
        } while (nbytes > 0);

        if (bReadFail)
            radio.evtdone(RM2_ERR_GENERIC, 0);
        else
            rx_done_isr(0);

        if (ghRxPipe != NULL) {
            printf("thread: rx handle open\n");
            break;
        }
    } // ...for (;;)

    dbg_rx_state = RS__EXITED;
    printf("[41mrx_thread stop[0m\n");
    return -1;
#if 0
#endif /* #if 0 */

}