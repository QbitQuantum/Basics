void ApplicationProtocol::recv(Ptr<Socket> socket)
{

    if(this->socket == 0)
        this->socket = socket;

    Address addr;
    uint8_t* buffer = 0;
    uint16_t bufferSize;
    bufferSize = socket->GetRxAvailable();
    buffer = (uint8_t*)calloc(bufferSize, 1);
    socket->RecvFrom(buffer, bufferSize, 0, addr);

    uint32_t msgNumber;
    ReliablePacket* packet = 0;

    switch(parseAppProtoHeader(buffer, addr, msgNumber))
    {

    case UNRELIABLE:
    case RELIABLE:

                forwardToApplication(buffer + headerSize, bufferSize - headerSize, addr);
                free(buffer);
                while((packet = getAllOrdered(addr, ++msgNumber)))
                {
                    forwardToApplication(packet->buffer + headerSize, packet->msgSize - headerSize, addr);
                    lastOrderedNumber[addr] = msgNumber;
                    packetsToAck[addr].push_back(msgNumber);
                    delete packet;
                }

                if(delayedAck == 0)
                {
                    ackAllPackets();
                }

            break;

        case UNORDERED:
            packetsOutOfOrder.push_back(new ReliablePacket(msgNumber, bufferSize, buffer, addr));

            break;

        case DUPLICATE: //this is already handled
        case ACK:  //this is only ack, do not forward to application
            break;

        case ERROR:
            PRINT_ERROR("Mysterious error occured in application layer protocol." << std::endl);
            break;
    }

}