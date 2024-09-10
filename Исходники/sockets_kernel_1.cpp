    int listener::
    accept (
        connection*& new_connection,
        unsigned long timeout
    )
    {
        SOCKET incoming;
        sockaddr_in incomingAddr;
        int length = sizeof(sockaddr_in);

        // implement timeout with select if timeout is > 0
        if (timeout > 0)
        {
            fd_set read_set;
            // initialize read_set
            FD_ZERO(&read_set);

            // add the listening socket to read_set
            FD_SET(listening_socket, &read_set);

            // setup a timeval structure
            timeval time_to_wait;
            time_to_wait.tv_sec = static_cast<long>(timeout/1000);
            time_to_wait.tv_usec = static_cast<long>((timeout%1000)*1000);


            // wait on select
            int status = select(0,&read_set,0,0,&time_to_wait);

            // if select timed out
            if (status == 0)
                return TIMEOUT;
            
            // if select returned an error
            if (status == SOCKET_ERROR)
                return OTHER_ERROR;

        }


        // call accept to get a new connection
        incoming=::accept(listening_socket,reinterpret_cast<sockaddr*>(&incomingAddr),&length);

        // if there was an error return OTHER_ERROR
        if ( incoming == INVALID_SOCKET )
            return OTHER_ERROR;
        

        // get the port of the foreign host into foreign_port
        int foreign_port = ntohs(incomingAddr.sin_port);

        // get the IP of the foreign host into foreign_ip
        std::string foreign_ip;
        {
            char* foreign_ip_temp = inet_ntoa(incomingAddr.sin_addr);

            // check if inet_ntoa() returned an error
            if (foreign_ip_temp == NULL)
            {
                closesocket(incoming);
                return OTHER_ERROR;            
            }

            foreign_ip.assign(foreign_ip_temp);
        }


        // get the local ip
        std::string local_ip;
        if (inaddr_any == true)
        {
            sockaddr_in local_info;
            length = sizeof(sockaddr_in);
            // get the local sockaddr_in structure associated with this new connection
            if ( getsockname (
                    incoming,
                    reinterpret_cast<sockaddr*>(&local_info),
                    &length
                 ) == SOCKET_ERROR 
            )
            {   // an error occurred
                closesocket(incoming);
                return OTHER_ERROR;
            }
            char* temp = inet_ntoa(local_info.sin_addr);
            
            // check if inet_ntoa() returned an error
            if (temp == NULL)
            {
                closesocket(incoming);
                return OTHER_ERROR;            
            }
            local_ip.assign(temp);
        }
        else
        {
            local_ip = listening_ip;
        }


        // set the SO_OOBINLINE option
        int flag_value = 1;
        if (setsockopt(incoming,SOL_SOCKET,SO_OOBINLINE,reinterpret_cast<const char*>(&flag_value),sizeof(int)) == SOCKET_ERROR )
        {
            closesocket(incoming);
            return OTHER_ERROR;  
        }


        // make a new connection object for this new connection
        try 
        { 
            new_connection = new connection (
                                    incoming,
                                    foreign_port,
                                    foreign_ip,
                                    listening_port,
                                    local_ip
                                ); 
        }
        catch (...) { closesocket(incoming); return OTHER_ERROR; }

        return 0;
    }