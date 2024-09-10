void CannBallNetworkManager::EstablishPeerConnection(int playerNum)
{
    UDPBroadcast broadcast;
    broadcast.SetMessage(to_string(CONNECT_MAGIC_NUM) + (playerNum == 1 ? "-PLAY1" : "-PLAY2"));
    broadcast.SetBroadcastPort(playerNum == 1 ? BROADCAST_PORT_P1 : BROADCAST_PORT_P2);
    
    SocketStream& peer = (playerNum == 1 ? m_player1 : m_player2);
    // TODO: REFACTOR THIS SHIT!
    broadcast.start();
    while(true) // Not needed? Just call broadcast.waitForFinish()???
    {
        if(!broadcast.isRunning())
        {
            broadcast.waitForFinish();

            cout << "OffworldNetManager P" << playerNum << ": Broadcast finished." << endl;
            SocketAddr peerAddr;
            if(!broadcast.GetPeerAddr(peerAddr))
            {
                cout << "OffworldNetManager P" << playerNum << ": Broadcast failed to find peer."
                     << endl;
                break;
            }

            cout << "OffworldNetManager P" << playerNum 
                 << ": Broadcast found peer. Attempting to connect" << endl;

            SocketAddr peerAddrStreamPort(peerAddr.GetIpAddr(), STREAM_PORT);
            Sleep(20); // Sleep gives peer time to setup their end.
            SetThreadAffinityMask(GetHandle(), 2);

            if(peer.Open(peerAddrStreamPort, 0))
            {
                // managed to connect.
                cout << "Connection to peer [" << peer.GetPeerAddr().ToString() << "]" 
                     << endl;

                char recvBuffer[100000];
                memset(recvBuffer, 0, 100000);
                if (peer.Recv(recvBuffer, 100000, 0) > 0)
                {
                    std::stringstream ssBuffer(recvBuffer);
                    std::string head;
                    ssBuffer >> head;
                    if(!head.compare("INIT"))
                    {
                        // Now read in entities.
                        while(!ssBuffer.eof())
                        {
                            std::string entityId;
                            ssBuffer >> head;
                            if(!head.compare("ENT"))
                            {                                
                                // Load in entity data.
                                ssBuffer >> entityId;
                                 
                                entityId =/* "P" + to_string(playerNum) + */entityId;
                                // What is it? Circle, Square?
                                std::string entityType;
                                ssBuffer >> entityType;
                                if(!entityType.compare("CIRC"))
                                {
                                    LoadCircle(ssBuffer, entityId);

                                    // Update circle to follow if it matches the player we're following.
                                    if (playerNum == m_playerNum)
                                    {
                                        m_followBallStr = entityId;
                                    }
                                       // m_followBall = m_scene->GetEntitySafe(entityId);
                                }
                                else if(!entityType.compare("SQR"))
                                {
                                    LoadSquare(ssBuffer, entityId);
                                }    
                                else if (!entityType.compare("CAN"))
                                {
                                    LoadCannon(ssBuffer, entityId);
                                }
                            }
                        }  
                        
                        int sentBytes = 0;
                        //while(sentBytes < 3)
                        //{ // Keep trying until sent all the data. Should send straight away without issues though.
                            // NOTE: Probably best to put something like this within the Send buffer.
                            sentBytes = peer.Send("ACK", 3, 0);
                        //}

                    }
                }