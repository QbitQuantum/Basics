int main(void)
{
	setup();

	while(1)
	{
		
		if(udp.recv(recvBuf))
		{
			uart1.printf("\r\n============================");		
			uart1.printf("\r\n本地端口:%d",udp.localPort );
			uart1.printf("\r\n消息来源:%d.%d.%d.%d:%d", udp.remoteIP[0],udp.remoteIP[1],udp.remoteIP[2],udp.remoteIP[3],udp.remotePort);
			uart1.printf("\r\n数据长度:%d",len);		
			uart1.printf("\r\n数据内容:");		
			uart1.printf((const char *)recvBuf);
			udp.sendto(udp.remoteIP,udp.remotePort,recvBuf,100);
		}
//		udp.sendto(rip,8080,data,60);
//		delay_ms(500);




		

	}


}