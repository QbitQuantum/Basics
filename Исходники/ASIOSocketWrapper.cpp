void ASIOSocketWrapper::sendProtocolHeader(const MultiplexedSocketPtr&parentMultiSocket, const Address& address,  const UUID&value, unsigned int numConnections) {
//    if (paerntMultiSocket->isZeroDelim()) {
    std::stringstream header;
    header << "GET /" << value.toString() << " HTTP/1.1\r\n";
    header << "Upgrade: WebSocket\r\n";
    header << "Connection: Upgrade\r\n";

    std::string hostname=address.getHostName();
    for (std::string::iterator hi=hostname.begin(),he=hostname.end(); hi!=he; ++hi) {
        *hi=std::tolower(*hi);
    }
    header << "Host: " << hostname;
    if (address.getService()!="80")
        header << ":" << address.getService();
    header << "\r\n";

    header << "Origin: " << address.getHostName() << "\r\n";

    if (parentMultiSocket->getStreamType()!= TCPStream::RFC_6455) {
        header << "Sec-WebSocket-Key1: x!|6 j9  U 1 guf  36Y04  |   4\r\n";
        header << "Sec-WebSocket-Key2: 3   59   2 E4   _11  x80      \r\n";
    } else {
        header << "Sec-WebSocket-Version: 13\r\n";
        header << "Sec-WebSocket-Key: MTIzNDU2Nzg5MGFiY2RlZg==\r\n";
    }
    header << "Sec-WebSocket-Protocol: "
           << (parentMultiSocket->getStreamType()==TCPStream::BASE64_ZERODELIM?"wssst":"sst")
           << numConnections << "\r\n";
    header << "\r\n";
    if (parentMultiSocket->getStreamType()!= TCPStream::RFC_6455) {
        header << "abcdefgh";
    }

    std::string finalHeader(header.str());
    Chunk * headerData= new Chunk(finalHeader.begin(),finalHeader.end());
    rawSend(parentMultiSocket,headerData,true);
    /*
        }else {
            UUID return_value=(parentMultiSocket->isZeroDelim()?massageUUID(UUID::random()):UUID::random());

            Chunk *headerData=new Chunk(TCPStream::TcpSstHeaderSize);
            copyHeader(&*headerData->begin(),parentMultiSocket->isZeroDelim()?TCPStream::WEBSOCKET_STRING_PREFIX():TCPStream::STRING_PREFIX(),value,numConnections);
            rawSend(parentMultiSocket,headerData,true);
        }
    */
}