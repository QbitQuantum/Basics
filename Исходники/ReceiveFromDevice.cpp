wxThread::ExitCode ReceiveFromDevice::Entry()
{
    bool error = false;//Indicates last state
    while(!TestDestroy())
    {
        DWORD read = 0;
        UCHAR buff[256]= {0};
        if(device->WinUSBHandle == INVALID_HANDLE_VALUE || !device->GetState())
        {
            Reset();
            if(error)
                Sleep(errSleep);
            error = true;
            continue;
        }
        OVERLAPPED overlapped;
        ZeroMemory(&overlapped, sizeof(overlapped));
        overlapped.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);//(NULL, TRUE, FALSE, NULL);
        if(!WinUsb_ReadPipe(device->WinUSBHandle, IN_EP, data + received, IN_EP_PACKET, &read, &overlapped))
        {
            if(GetLastError() != ERROR_IO_PENDING)
            {
                Reset();
                if(error)
                    Sleep(errSleep);
                error = true;
                continue;
            }
        }
        while(WaitForSingleObject(overlapped.hEvent, 100) == WAIT_TIMEOUT)
        {
            if(TestDestroy())//Check whether the thread should be destroyed
            {
                CloseHandle(overlapped.hEvent);
                return 0;
            }
        }
        //Complete transfer - get received bytes
        WinUsb_GetOverlappedResult(device->WinUSBHandle, &overlapped, &read, FALSE);
        CloseHandle(overlapped.hEvent);//Clear event
        //Process data
        if(read == 0)
        {
            //Error occur, reset state
            Reset();
            if(error)
                Sleep(errSleep);
            error = true;
            continue;
        }
        error = false;
        //Increase counters
        received += read;
        receivedPackets++;
        //Check if we read entire message
        if(data[0] == receivedPackets)
        {
            ProcessMessage();
            Reset();
        }
    }
    return 0;
}