int main(void)
{
    setup();

    while(1)
    {

        if(udp1.recv(buf))
        {
            uart1.printf("\r\n============================");
            uart1.printf("\r\n本地端口:%d", udp1.localPort );
            uart1.printf("\r\n消息来源:%d.%d.%d.%d:%d", udp1.remoteIP[0], udp1.remoteIP[1], udp1.remoteIP[2], udp1.remoteIP[3], udp1.remotePort);
            uart1.printf("\r\n数据内容:");
            uart1.printf((const char *)buf);
            udp1.sendto(udp1.remoteIP, udp1.remotePort, buf, 100);
        }
        if(udp2.recv(buf))
        {
            uart1.printf("\r\n============================");
            uart1.printf("\r\n本地端口:%d", udp2.localPort );
            uart1.printf("\r\n消息来源:%d.%d.%d.%d:%d", udp2.remoteIP[0], udp2.remoteIP[1], udp2.remoteIP[2], udp2.remoteIP[3], udp2.remotePort);
            uart1.printf("\r\n数据内容:");
            uart1.printf((const char *)buf);
            udp2.sendto(udp2.remoteIP, udp2.remotePort, buf, 100);
        }

    }


}