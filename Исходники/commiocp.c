/* write operation on common fd (udp)
 * @Handle -- the common fd
 * @Dst -- destination address information
 * @DstLen -- sizeof Dst
 * @Buffer -- data buffer
 * @BufferSize -- size of data to write
 * @Callback -- callback function when write successful
 * @Args -- argument to callback
 * return TRUE -- success, else error
 */
BOOL 
CommIOCPUdpWrite(
    COMMFD_HANDLE Handle, 
    PSOCKADDR Dst,
    INT DstLen,
    PBYTE Buffer, 
    DWORD BufferSize, 
    WRITE_CALLBACK Callback,
    PVOID Args
    )
{
    INT Ret;
    PCOMMIOCP CommIOCP;
    PCOMM_SOCKET_IO_CTX IOData;
    DWORD Flags = 0, Bytes = 0;
    PCOMMFD Commfd = (PCOMMFD)Handle;

    if (!Callback || !Commfd || Commfd->Type != COMM_UDP || Commfd->Handle.Socket == INVALID_SOCKET) {
        LOG_ERROR("bad args");
        return (FALSE);
    }

    CommIOCP = Commfd->CommIOCP;
    
    IOData = (PCOMM_SOCKET_IO_CTX)CommIOCPIOCtxCreate(Commfd->CommIOCP, IO_SOCK_WRITE);
    if (IOData == NULL) {
        LOG_ERROR("create socket IO context failed");
        return (FALSE);
    }

    IOData->WSABuffer.buf = (CHAR *)Buffer;
    IOData->WSABuffer.len = BufferSize;
    IOData->Data.Callback.Write = Callback;
    IOData->Data.Args = Args;

    CommIOCPFDAddRef(Commfd);
    Ret = WSASendTo(Commfd->Handle.Socket, &IOData->WSABuffer, 1, &Bytes, Flags, Dst, DstLen, &IOData->Data.OL, NULL);

    if (Ret == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING) {
        LOG_ERROR("WSASendTo failed [%d]", WSAGetLastError());
        CommIOCPIOCtxDestroy(Commfd->CommIOCP, &IOData->Data);
        CommIOCPFDRelease(Commfd);
        return (FALSE);
    }

    return (TRUE);
}