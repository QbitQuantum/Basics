    void NamedPipe::Initialize()
    {
        SECURITY_ATTRIBUTES attr;
        attr.bInheritHandle = TRUE;
        attr.nLength = sizeof(SECURITY_ATTRIBUTES);
        attr.lpSecurityDescriptor = NULL;

        mHandle = CreateFileA(
            mName.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            &attr,
            OPEN_EXISTING,
            0,
            NULL);

        if (mHandle == INVALID_HANDLE) {
            mHandle = CreateNamedPipeA(
                mName.c_str(),
                PIPE_ACCESS_DUPLEX,
                PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
                PIPE_UNLIMITED_INSTANCES,
                65536,
                65536,
                NMPWAIT_WAIT_FOREVER,
                &attr);

            if (mHandle == INVALID_HANDLE) {
                throw NamedPipeException(GetLastErrorString());
            } else if (!ConnectNamedPipe(mHandle, NULL) && GetLastError() != ERROR_PIPE_CONNECTED) {
                throw NamedPipeException(GetLastErrorString());
            }
        }
    }