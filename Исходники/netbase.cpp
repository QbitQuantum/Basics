bool NetBase::CheckIn()
{    
    // check for incoming packets
    SOCKADDR_IN addr;
    memset (&addr, 0, sizeof(SOCKADDR_IN));
    socklen_t len = sizeof(SOCKADDR_IN);

    if (!input_buffer)
    {
        input_buffer = (char*) cs_malloc(MAXPACKETSIZE);

        if (!input_buffer)
        {
            Error2("Failed to cs_malloc %d bytes for packet buffer!\n",MAXPACKETSIZE);
            return false;
        }
    }

    // Connection must be initialized!
    CS_ASSERT(ready);
    
    int packetlen = RecvFrom (&addr, &len, (void*) input_buffer, MAXPACKETSIZE);

    if (packetlen <= 0)
    {
        return false;
    }
    // Identify the connection
    Connection* connection = GetConnByIP(&addr);

    // Extract the netpacket from the buffer and prep for use locally.
    psNetPacket *bufpacket = psNetPacket::NetPacketFromBuffer(input_buffer,packetlen);
    if (bufpacket==NULL)
    {
        char addrText[INET_ADDRSTRLEN];

        //for win32 for now only inet_ntoa as inet_ntop wasn't supported till vista.
        //it has the same degree of compatibility of the previous code and it's supported till win2000
        #ifdef WIN32
        strncpy(addrText, inet_ntoa(addr.sin_addr), INET_ADDRSTRLEN);
        #else
        //there was a failure in conversion if null
        if(!inet_ntop(addr.sin_family,&addr.sin_addr, addrText, sizeof(addrText)))
        {
            strncpy(addrText, "UNKNOWN", INET_ADDRSTRLEN);
        }
        #endif

        // The data received was too small to make a full packet.
        if (connection)
        {
            Debug4(LOG_NET, connection->clientnum, "Too short packet received from client %d (IP: %s) (%d bytes)", connection->clientnum, addrText, packetlen);
        }
        else
        {
            Debug3(LOG_NET, 0, "Too short packet received from IP address %s. (%d bytes) No existing connection from this IP.",
                addrText, packetlen);
        }
        return true; // Continue processing more packets if available
    }
    input_buffer = NULL; //input_buffer now hold by the bufpacket pointer.

    // Endian correction
    bufpacket->UnmarshallEndian();

    // Check for too-big packets - no harm in processing them, but probably a bug somewhere
    if (bufpacket->GetPacketSize() < static_cast<unsigned int>(packetlen))
    {
        char addrText[INET_ADDRSTRLEN];

        //for win32 for now only inet_ntoa as inet_ntop wasn't supported till vista.
        //it has the same degree of compatibility of the previous code and it's supported till win2000
        #ifdef WIN32
        strncpy(addrText, inet_ntoa(addr.sin_addr), INET_ADDRSTRLEN);
        #else
        //there was a failure in conversion if null
        if(!inet_ntop(addr.sin_family,&addr.sin_addr, addrText, sizeof(addrText)))
        {
            strncpy(addrText, "UNKNOWN", INET_ADDRSTRLEN);
        }
        #endif
        
        if (connection)
        {
            Debug5(LOG_NET, connection->clientnum, "Too long packet received from client %d (IP: %s) (%d bytes received, header reports %zu bytes)",
                connection->clientnum, addrText, packetlen, bufpacket->GetPacketSize());
        }
        else
        {
            
            Debug4(LOG_NET, 0,"Too long packet received from IP address %s. (%d bytes received, header reports %zu bytes) No existing connection from this IP.",
                   addrText, packetlen, bufpacket->GetPacketSize());
        }
    }

    //Create new net packet entry and transfer ownership of bufpacket to pkt.
    csRef<psNetPacketEntry> pkt;
    pkt.AttachNew(new psNetPacketEntry( bufpacket, 
            connection ? connection->clientnum : 0, packetlen));
    
    if(TEST_PACKETLOSS > 0.0 && randomgen->Get() < TEST_PACKETLOSS)
    {
        psNetPacket* packet = pkt->packet;
        int type = 0;

        if (packet->offset == 0) 
        {
            psMessageBytes* msg = (psMessageBytes*) packet->data;
            type = msg->type;
        }

        Error3("Packet simulated lost. Type %s ID %d.\n", type == 0 ? "Fragment" : (const char *)  GetMsgTypeName(type), pkt->packet->pktid);
        return true;
    }

    // ACK packets can get eaten by HandleAck
    if (HandleAck(pkt, connection, &addr))
    {
        return true;
    }

    // printf("Got packet with sequence %d.\n", pkt->packet->GetSequence());
    //
    // Check for doubled packets and drop them
    if (pkt->packet->pktid != 0)
    {
        if (connection && CheckDoublePackets (connection, pkt))
        {
#ifdef PACKETDEBUG
            Debug2(LOG_NET,0,"Dropping doubled packet (ID %d)\n", pkt->packet->pktid);
#endif
            return true;
        }
    }
    
#ifdef PACKETDEBUG
    Debug7(LOG_NET,0,"Received Pkt, ID: %d, offset %d, from %d size %d (actual %d) flags %d\n", 
        pkt->packet->pktid, pkt->packet->offset, pkt->clientnum, pkt->packet->pktsize,packetlen, pkt->packet->flags);
#endif

    /**
    * Now either send this packet to BuildMessage, or loop through
    * subpackets if they are merged.
    */
    csRef<psNetPacketEntry> splitpacket = pkt;
    psNetPacket      *packetdata = NULL;

    do
    {
        splitpacket = pkt->GetNextPacket(packetdata);
        if (splitpacket)
            BuildMessage(splitpacket, connection, &addr);
    } while (packetdata);
    return true;
}