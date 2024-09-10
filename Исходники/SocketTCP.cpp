////////////////////////////////////////////////////////////
/// Connect to another computer on a specified port
////////////////////////////////////////////////////////////
Socket::Status SocketTCP::Connect(unsigned short Port, const IPAddress& HostAddress, float Timeout)
{
    // Make sure our socket is valid
    if (!IsValid())
        Create();

    // Build the host address
    sockaddr_in SockAddr;
    memset(SockAddr.sin_zero, 0, sizeof(SockAddr.sin_zero));
    SockAddr.sin_addr.s_addr = inet_addr(HostAddress.ToString().c_str());
    SockAddr.sin_family      = AF_INET;
    SockAddr.sin_port        = htons(Port);

    if (Timeout <= 0)
    {
        // ----- We're not using a timeout : just try to connect -----

        if (connect(mySocket, reinterpret_cast<sockaddr*>(&SockAddr), sizeof(SockAddr)) == -1)
        {
            // Failed to connect
            return SocketHelper::GetErrorStatus();
        }

        // Connection succeeded
        return Socket::Done;
    }
    else
    {
        // ----- We're using a timeout : we'll need a few tricks to make it work -----

        // Save the previous blocking state
        bool IsBlocking = myIsBlocking;

        // Switch to non-blocking to enable our connection timeout
        if (IsBlocking)
            SetBlocking(false);

        // Try to connect to host
        if (connect(mySocket, reinterpret_cast<sockaddr*>(&SockAddr), sizeof(SockAddr)) >= 0)
        {
            // We got instantly connected! (it may no happen a lot...)
            return Socket::Done;
        }

        // Get the error status
        Socket::Status Status = SocketHelper::GetErrorStatus();

        // If we were in non-blocking mode, return immediatly
        if (!IsBlocking)
            return Status;

        // Otherwise, wait until something happens to our socket (success, timeout or error)
        if (Status == Socket::NotReady)
        {
            // Setup the selector
            fd_set Selector;
            FD_ZERO(&Selector);
            FD_SET(mySocket, &Selector);

            // Setup the timeout
            timeval Time;
            Time.tv_sec  = static_cast<long>(Timeout);
            Time.tv_usec = (static_cast<long>(Timeout * 1000) % 1000) * 1000;

            // Wait for something to write on our socket (which means that the connection request has returned)
            if (select(static_cast<int>(mySocket + 1), NULL, &Selector, NULL, &Time) > 0)
            {
                // At this point the connection may have been either accepted or refused.
                // To know whether it's a success or a failure, we try to retrieve the name of the connected peer
                SocketHelper::LengthType Size = sizeof(SockAddr);
                if (getpeername(mySocket, reinterpret_cast<sockaddr*>(&SockAddr), &Size) != -1)
                {
                    // Connection accepted
                    Status = Socket::Done;
                }
                else
                {
                    // Connection failed
                    Status = SocketHelper::GetErrorStatus();
                }
            }
            else
            {
                // Failed to connect before timeout is over
                Status = SocketHelper::GetErrorStatus();
            }
        }

        // Switch back to blocking mode
        SetBlocking(true);

        return Status;
    }
}