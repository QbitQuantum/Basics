void CTeleSerialHandler::List(TcpSocket *sendto)
{
    int ii=0;
    tprintf(sendto, "Handler Socket List\n");
    tprintf(sendto, "------------------------------\n");
    for (socket_m::iterator it = m_sockets.begin(); it != m_sockets.end(); it++, ii++)
    {
        Socket *p = (*it).second;
        TcpSocket *p3 = dynamic_cast<TcpSocket *>(p);
#ifdef TeleSerial_FUNC_UDPSOCKETSERVER

        CTeleSerialUdpSocket *pCGeneralAgentUdpSocket = dynamic_cast<CTeleSerialUdpSocket *>(p);
#else

        Socket *pCGeneralAgentUdpSocket = NULL;
#endif

        if (p->GetRemotePort()<=0 || pCGeneralAgentUdpSocket)
        {
            //__trip;
            continue;
        }

        tprintf(sendto, "%-3d %15s:%-5d", ii, p -> GetRemoteAddress().c_str(),p -> GetRemotePort());
        tprintf(sendto, "  %9s  %s %s", p -> Ready() ? "Ready" : "NOT Ready", p->GetSockName().c_str(), p -> IsConnected() ? "Conned" : "NOT Conned");
#if 0

        CTeleSerialTcpSocketServer *pServer = dynamic_cast<CTeleSerialTcpSocketServer *>(p);
        CTeleSerialTcpSocketConnector *pConnector = dynamic_cast<CTeleSerialTcpSocketConnector *>(p);
#ifdef TeleSerial_FUNC_STATUS_AGENT

        CTeleSerialStatusAgent *p4 = dynamic_cast<CTeleSerialStatusAgent *>(p);
        if (p4)
        {
            tprintf(sendto, "CTeleSerialStatusAgent");
        }
        else
#endif
            if (pServer)
            {
                tprintf(sendto, "CTeleSerialTcpSocketServer");
            }
            else if (pConnector)
            {
                tprintf(sendto, "CTeleSerialTcpSocketConnector");
            }
            else
            {
                tprintf(sendto, "Socket");
            }
#endif
        tprintf(sendto, "\n");
        tprintf(sendto, "\tUptime:  %d days %02d:%02d:%02d\n",
                p -> Uptime() / 86400,
                (p -> Uptime() / 3600) % 24,
                (p -> Uptime() / 60) % 60,
                p -> Uptime() % 60);
        if (p3 || pCGeneralAgentUdpSocket)
        {
            tprintf(sendto, "\tBytes Read: %9lu\n",p -> GetBytesReceived());
            tprintf(sendto, "\tBytes Sent: %9lu\n",p -> GetBytesSent());
        }
    }
    tprintf(sendto, "\n");
}