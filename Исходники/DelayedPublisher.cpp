    void ProcessDelayedPackets(DWORD timestamp)
    {
        if(bCancelEnd)
            return;

        if(timestamp >= delayTime)
        {
            if(!bConnected && !bConnecting && !bStopping)
            {
                hConnectionThread = OSCreateThread((XTHREAD)CreateConnectionThread, this);
                bConnecting = true;
            }

            if(bConnected)
            {
                if(!bDelayConnected)
                {
                    delayTime = timestamp;
                    bDelayConnected = true;
                }

                DWORD sendTime = timestamp-delayTime;
                for(UINT i=0; i<delayedPackets.Num(); i++)
                {
                    NetworkPacket &packet = delayedPackets[i];
                    if(packet.timestamp <= sendTime)
                    {
                        RTMPPublisher::SendPacket(packet.data.Array(), packet.data.Num(), packet.timestamp, packet.type);
                        packet.data.Clear();
                        delayedPackets.Remove(i--);
                    }
                }
            }
        }
    }