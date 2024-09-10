SInt64 ProxyTask::Run()
{
    const UInt32 kMaxRTCPPacketSize = 2048;
    char thePacketBuffer[kMaxRTCPPacketSize];
    QTSS_PacketStruct thePacketStruct;
    thePacketStruct.packetTransmitTime = QTSS_Milliseconds();
    thePacketStruct.packetData = thePacketBuffer;

    (void)this->GetEvents();    

    OSMutexLocker locker(sSocketPool->GetMutex());
    for (OSQueueIter iter(sSocketPool->GetSocketQueue()); !iter.IsDone(); iter.Next())
    {
        UInt32 theRemoteAddr = 0;
        UInt16 theRemotePort = 0;

        UDPSocketPair* thePair = (UDPSocketPair*)iter.GetCurrent()->GetEnclosingObject();
        Assert(thePair != NULL);
        
        for (UInt32 x = 0; x < 2; x++)
        {
            QTSS_WriteFlags theFlags = qtssWriteFlagsNoFlags;
            
            UDPSocket* theSocket = NULL;
            if (x == 0)
            {
                theFlags = qtssWriteFlagsIsRTP;
                theSocket = thePair->GetSocketA();
            }
            else
            {
                theFlags = qtssWriteFlagsIsRTCP;
                theSocket = thePair->GetSocketB();
            }
            
            Assert(theSocket->GetDemuxer() != NULL);
            OSMutexLocker locker(theSocket->GetDemuxer()->GetMutex());
            
            //get all the outstanding packets for this socket
            while (true)
            {
                UInt32 thePacketLen = 0;
                theSocket->RecvFrom(&theRemoteAddr, &theRemotePort, thePacketStruct.packetData, 
                                kMaxRTCPPacketSize, &thePacketLen);
                if (thePacketLen == 0)
                    break;//no more packets on this socket!
                    
                ProxyDemuxerTask* theDemuxerTask = (ProxyDemuxerTask*)theSocket->GetDemuxer()->GetTask(theRemoteAddr, 0);
                if (theDemuxerTask != NULL)
                {
                    QTSS_RTPStreamObject theStream = theDemuxerTask->GetStream();
                    (void)QTSS_Write(theStream, &thePacketStruct, thePacketLen, NULL, theFlags);
                }
            }
        }
    }
    return kProxyTaskPollIntervalMsec;
}