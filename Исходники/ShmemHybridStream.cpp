int ShmemHybridStream::connect(const ACE_INET_Addr& ace_address)
{
    if (m_bLinked) return -1;

    ACE_SOCK_Connector connector;
    YARP_SSIZE_T result=connector.connect(m_SockStream,ace_address);
    if (result<0)
    {
        YARP_ERROR(Logger::get(),ConstString("ShmemHybridStream client returned ")+NetType::toString((int)result));
        close();
        return -1;
    }

    ACE_INET_Addr local,remote;
    m_SockStream.get_local_addr(local);
    m_SockStream.get_remote_addr(remote);
    m_LocalAddress=Contact(local.get_host_addr(),local.get_port_number());
    m_RemoteAddress=Contact(remote.get_host_addr(),remote.get_port_number());

    out.open(m_LocalAddress.getPort());

    ShmemPacket_t send_conn_data;
    send_conn_data.command=CONNECT;
    send_conn_data.size=SHMEM_DEFAULT_SIZE;
    result=m_SockStream.send_n(&send_conn_data,sizeof send_conn_data);
    if (result<=0)
    {
        YARP_ERROR(Logger::get(),ConstString("Socket returned ")+NetType::toString((int)result));
        close();
        return -1;
    }

    ShmemPacket_t recv_conn_data;
    result=m_SockStream.recv_n(&recv_conn_data,sizeof recv_conn_data);
    if (result<=0)
    {
        YARP_ERROR(Logger::get(),ConstString("Socket returned ")+NetType::toString((int)result));
        close();
        return -1;
    }

    in.open(m_RemoteAddress.getPort(),&m_SockStream);

    m_bLinked=true;

    m_SockStream.enable(ACE_NONBLOCK);

    return 0;
}