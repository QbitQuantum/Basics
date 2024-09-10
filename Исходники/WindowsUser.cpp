    void WindowsUser::logout()
    {
        // Free the buffer for the logon SID.

        if (pSid_)
        {
            freeLogonSID(&pSid_);
        }

        // Close the handles to the interactive window station and desktop.

        if (winstaHandle_)
        {
            CloseWindowStation(winstaHandle_);
            winstaHandle_ = NULL;
        }

        if (deskHandle_)
        {
            CloseDesktop(deskHandle_);
            deskHandle_ = NULL;
        }

        // Close the handle to the client's access token.

        if (tokenHandle_)
        {
            RevertToSelf();
            CloseHandle(tokenHandle_);  
            tokenHandle_ = NULL;
        }
    }