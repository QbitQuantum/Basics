void SampleServer::on_register(uint32_t sid, uint8_t stype, uint16_t net_type, const Inet_Addr& tel_addr, const Inet_Addr& cnc_addr)
{
	SAM_INFO("on_register sid = " << sid << ", stype = " << GetServerName(stype) << ", tel addr = " << tel_addr << ", cnc addr = " << cnc_addr);

	//启动第一次收到登记结果，如果timer id != 0表示有可能是本服务与daemond之间TCP断开后进行了重新连接！！！
	if(timer_id_ == 0)
	{
		//保存地址信息
		if(CHECK_CNC_NETTYPE(net_type))
			SERVER_PORT = cnc_addr.get_port();
		else
			SERVER_PORT = tel_addr.get_port();

		SERVER_NET_TYPE = net_type;

		SERVER_ID = sid;
		TEL_IPADDR = tel_addr;
		CNC_IPADDR = cnc_addr;

		//绑定服务端口，包括tcp udp监听端口
		SAMPLE_FRAME()->bind_port(SERVER_PORT);

		//设置心跳事件
		set_timer();
	}
}