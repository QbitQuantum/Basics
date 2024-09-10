void Mud::processNewConnection()
{
    // The file descriptor for the new socket.
    int socketFileDescriptor;
    struct sockaddr_in socketAddress;
    socklen_t socketAddressSize = sizeof(socketAddress);

    // Loop until all outstanding connections are accepted.
    while (true)
    {
        try
        {
            socketFileDescriptor = accept(_servSocket, (struct sockaddr *) &socketAddress, &socketAddressSize);

            // A bad socket probably means no more connections are outstanding.
            if (socketFileDescriptor == kNoSocketIndicator)
            {
                // blocking is OK - we have accepted all outstanding connections.
                if (errno == EWOULDBLOCK)
                {
                    return;
                }
                throw std::runtime_error("ACCEPT");
            }

            // Here on successful accept - make sure socket doesn't block.
#ifdef __linux__
            if (fcntl(socketFileDescriptor, F_SETFL, FNDELAY) == -1)
            {
                throw std::runtime_error("FCNTL on player socket");
            }
#elif __APPLE__
            if (fcntl(socketFileDescriptor, F_SETFL, FNDELAY) == -1)
            {
                throw std::runtime_error("FCNTL on player socket");
            }
#elif __CYGWIN__

            int flags = fcntl(_servSocket, F_GETFL, 0);
            //if (fcntl(_servSocket, F_SETFL, flags | O_NONBLOCK | O_RDWR | O_NOCTTY | O_NDELAY) == -1)
            if (fcntl(_servSocket, F_SETFL, flags | O_NDELAY | O_NONBLOCK) == -1)
            {
                throw std::runtime_error("FCNTL on player socket");
            }
#elif _WIN32
            u_long imode = 1;
            if (ioctlsocket(_servSocket, FIONBIO, &imode) == -1)
            {
                throw std::runtime_error("FCNTL on Control Socket");
            }
#endif

            std::string address = inet_ntoa(socketAddress.sin_addr);
            int port = ntohs(socketAddress.sin_port);

            // Immediately close connections from blocked IP addresses.
            if (blockedIPs.find(address) != blockedIPs.end())
            {
                Logger::log(LogLevel::Global, "Rejected connection from " + address + "!");
                closeSocket(socketFileDescriptor);
                continue;
            }

            Player * player = new Player(socketFileDescriptor, port, address);

            // Insert the player in the list of players.
            addPlayer(player);

            Logger::log(LogLevel::Global, "#--------- New Connection ---------#");
            Logger::log(LogLevel::Global, " Socket  : " + ToString(socketFileDescriptor));
            Logger::log(LogLevel::Global, " Address : " + address);
            Logger::log(LogLevel::Global, " Port    : " + ToString(port));
            Logger::log(LogLevel::Global, "#----------------------------------#");

            // Activate the procedure of negotiation.
            NegotiateProtocol(player, ConnectionState::NegotiatingMSDP);
        }
        catch (std::exception & e)
        {
            Logger::log(LogLevel::Error, "Error during processing a new connection.");
            Logger::log(LogLevel::Error, "Error : " + std::string(e.what()));
            break;
        }
    }
}