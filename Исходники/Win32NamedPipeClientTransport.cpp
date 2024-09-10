    std::size_t Win32NamedPipeClientTransport::implRead(
        const ByteBuffer &byteBuffer,
        std::size_t bytesRequested)
    {
        // For now, can't go back to sync calls after doing an async call.
        // Limitations with Windows IOCP.
        RCF_ASSERT(!mAsyncMode);

        std::size_t bytesToRead = RCF_MIN(bytesRequested, byteBuffer.getLength());

        BOOL ok = ResetEvent(mhEvent);
        DWORD dwErr = GetLastError();
        RCF_VERIFY(ok, Exception(_RcfError_Pipe(), dwErr));

        OVERLAPPED overlapped = {0};
        overlapped.hEvent = mhEvent;

        DWORD dwRead = 0;
        DWORD dwBytesToRead = static_cast<DWORD>(bytesToRead);

        ok = ReadFile(
            mhPipe, 
            byteBuffer.getPtr(), 
            dwBytesToRead, 
            &dwRead, 
            &overlapped);
        
        dwErr = GetLastError();

        if (!ok)
        {
            RCF_VERIFY( 
                dwErr == ERROR_IO_PENDING ||
                dwErr == WSA_IO_PENDING ||
                dwErr == ERROR_MORE_DATA,
                Exception(_RcfError_ClientReadFail(), dwErr));
        }

        ClientStub & clientStub = *getTlsClientStubPtr();

        DWORD dwRet = WAIT_TIMEOUT;
        while (dwRet == WAIT_TIMEOUT)
        {
            boost::uint32_t timeoutMs = generateTimeoutMs(mEndTimeMs);
            timeoutMs = clientStub.generatePollingTimeout(timeoutMs);

            dwRet = WaitForSingleObject(overlapped.hEvent, timeoutMs);
            dwErr = GetLastError();

            RCF_VERIFY( 
                dwRet == WAIT_OBJECT_0 || dwRet == WAIT_TIMEOUT, 
                Exception(_RcfError_Pipe(), dwErr));

            RCF_VERIFY(
                generateTimeoutMs(mEndTimeMs),
                Exception(_RcfError_ClientReadTimeout()))
                (mEndTimeMs)(bytesToRead);

            if (dwRet == WAIT_TIMEOUT)
            {
                clientStub.onPollingTimeout();
            }
        }
        RCF_ASSERT_EQ(dwRet , WAIT_OBJECT_0);

        dwRead = 0;
        ok = GetOverlappedResult(mhPipe, &overlapped, &dwRead, FALSE);
        dwErr = GetLastError();
        RCF_VERIFY(ok && dwRead > 0, Exception(_RcfError_Pipe(), dwErr));

        onTimedRecvCompleted(dwRead, 0);

        return dwRead;
    }