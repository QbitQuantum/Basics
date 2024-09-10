BOOL enzyme::kernel::Service::stop()
{
    if(mHandle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(mHandle);
    }

    if(mSCHandle != INVALID_HANDLE_VALUE)
    {
        SERVICE_STATUS_PROCESS status;
        if(ControlService(mSCHandle, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&status))
        {
            DWORD timeout = GetTickCount() + 5000;
            while(status.dwCurrentState != SERVICE_STOPPED)
            {
                DWORD tmp;
                if(GetTickCount() >= timeout)
                {
                    std::clog << "Timeout stopping kernel driver" << std::endl;
                    break;
                }
                Sleep(50);
                if(!QueryServiceStatusEx(mSCHandle, SC_STATUS_PROCESS_INFO, (LPBYTE)&status, sizeof(SERVICE_STATUS_PROCESS), &tmp))
                {
                    break;
                }
            }
        }
        else if(GetLastError() != ERROR_SERVICE_NOT_ACTIVE)
        {
            std::clog << lasterror() << std::endl;
        }

        DeleteService(mSCHandle);
        return CloseServiceHandle(mSCHandle);
    }

    return TRUE;
}