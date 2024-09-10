void Network::update(unsigned long currentTime)
{
    std::cout<<__PRETTY_FUNCTION__<<std::endl;
    bUpdateInProgress = true;
    mCurrentTime = currentTime;
    boost::system::error_code errorCode;
    boost::asio::ip::udp::endpoint endpoint;

    ////////////////////////
    // Send packet for all connection
    ////////////////////////
    for (auto cit = mConnections.begin(); cit != mConnections.end(); )
    {
        Connection* c = cit->second;

        if (!c->isConnected() &&
            c->getSentTime() + mConnectionRequestRetryDelay <= currentTime)
        {
            requestConnection(c);
        }
        else if (c->getHeartbeat() + mConnectionTimeout <= currentTime)
        {
            destroyConnection(c, "connection timeout");
            ++cit;
            //c->clear();
            continue;
        }
        else if (c->getHeartbeat() + mResponseTimeout <= currentTime &&
                 c->getPingSentTime() + mPingRetryDelay <= currentTime)
        {
            c->sendPing(currentTime);
        }

        c->send(currentTime, mSocket);
        ++cit;
    }

    // Send packet to unconnected endpoint
    for (auto& b : mAddressedPackets)
    {
        std::cout<<"Sending addressed packet"<<std::endl;
        mSocket.send_to(
            boost::asio::buffer(b.buffer.data(), b.buffer.size()),
            b.endpoint, 0, errorCode);
    }
    mAddressedPackets.clear();

    ////////////////////////
    // Receive
    ////////////////////////
    Buffer* buffer = newBuffer();
    while (42)
    {

        buffer->size(mSocket.receive_from(
            boost::asio::buffer(buffer->data(), Buffer::Size),
            endpoint, 0, errorCode));

        if (!buffer->size()) break; // Nothing was received

        std::cout<<"Packet received"<<std::endl;

        Connection* connection = getConnection(endpoint);
        if (connection) 
        {
            std::cout<<"Ack received: "<<(unsigned)buffer->getAckCount()<<std::endl;
            if (buffer->hasAck())
            {
                for (unsigned char i = 0; i < buffer->getAckCount(); i++)
                {
                    std::cout<<"Ack received: id:"<<buffer->getAck(i)<<std::endl;
                    connection->ack(buffer->getAck(i));
                }
            }
        }

        switch (buffer->getType())
        {
            case PT_PING:
                if (connection) connection->handlePing();
                break;

            case PT_PONG:
                if (connection) connection->handlePong(currentTime);
                break;

            case PT_CONNECTION:
                handleConnection(buffer, endpoint);
                break;

            case PT_DATA:
                if (connection)
                {
                    // The buffer ownership is transfered to the connection
                    // TODO ???? eliminate this and use a callback for the connection to parse the packet ???????
                    connection->addIncomingBuffer(buffer, currentTime);
                    buffer = newBuffer(); // Get a new one
                }
                break;

            default:
                break;
        }
    }
    releaseBuffer(buffer);

    bUpdateInProgress = false;
    runQueuedJobs();
}