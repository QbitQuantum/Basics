void onMessage(const TcpConnectionPtr& conn,
                Buffer* buf,
                Timestamp receiveTime)
{
    if (buf->findCRLF())
    {
        conn->send("No such user\r\n");
        conn->shutdown();
    }
}