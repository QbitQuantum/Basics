void BaseSvr::onMessage(const TcpConnectionPtr& conn, Buffer* buf)
{
    LOG_INFO << "accept msg from <" << conn->name() << ">";

    string request(buf->peek(), buf->beginWrite());
    LOG_INFO << "received msg from client<" << conn->peerAddress().IpAndPort() << "> : <" << request << ">";

    conn->send(request);

    size_t len = 0;
    while((len = buf->readableBytes()) > 1)
    {
        // 本消息包除头部外剩余部分的长度
        size_t packetLen = endian::networkToHost16(buf->peekInt16());
        if(packetLen > len)
        {///< 缓冲区剩余空间反而大于消息包长度了 >
            conn->send("peek msg fail: packetLen > len of buffer\r\n");
            conn->shutdown();
            break;
        }

        if(false == protobufapi::checksum(buf->peek() + HEADER_LENGTH, packetLen))
        {///< 校验结果不匹配 >
            conn->send("server check sum error. your msg is discard");
            conn->shutdown();
            break;
        }

        Buffer *pMsg = new Buffer();
        pMsg->retrieveAll();
        pMsg->append(buf->peek() + sizeof int16_t, sizeof int16_t + packetLen - TAIL_LENGTH);

        m_msgQueue.put(pMsg);

        buf->retrieve(packetLen + HEADER_LENGTH);
    }
}