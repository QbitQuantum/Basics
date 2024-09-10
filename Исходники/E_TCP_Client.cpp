int main(void)
{
    setup();

    while(1)
    {

        len = tcp.recv(buf);
        if(len > 0)
        {
            uart1.printf("\r\n============================");
            uart1.printf("\r\n本地端口:%d",tcp.localPort );
            uart1.printf("\r\n消息来源:%d.%d.%d.%d:%d", tcp.remoteIP[0],tcp.remoteIP[1],tcp.remoteIP[2],tcp.remoteIP[3],tcp.remotePort);
            uart1.printf("\r\n数据长度:%d",len);
            uart1.printf("\r\n数据内容:");
            uart1.printf((const char *)buf);
            tcp.send(buf,len);
        }






    }


}