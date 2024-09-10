int main(void)
{
	setup();
	while(1)
	{
	  res=f_opendir(&DirObject,"/123");//打开目录
    if(res==FR_OK)
    {
      uart1.printf("\r\n打开目录成功 !\r\n");
      uart1.printf("该目录所在簇号：%d\r\n",DirObject.clust);
      uart1.printf("该目录所在扇区号：%d\r\n",DirObject.sect);
    }
    else if(res==FR_NO_PATH)
      uart1.printf("所找目录路径不存在\r\n");    
    else
      uart1.printf("打开目录失败~~~~(>_<)~~~~ \r\n");
		if(udp1.recv(buf))
		{
			uart1.printf("\r\n============================");		
			uart1.printf("\r\n本地端口:%d",udp1.localPort );
			uart1.printf("\r\n消息来源:%d.%d.%d.%d:%d", udp1.remoteIP[0],udp1.remoteIP[1],udp1.remoteIP[2],udp1.remoteIP[3],udp1.remotePort);
			uart1.printf("\r\n数据内容:");		
			uart1.printf((const char *)buf);		
			uart1.printf("\r\n============================");		
			udp1.sendto(udp1.remoteIP,udp1.remotePort,buf,100);
		}
		delay_ms(1000);
	}


}