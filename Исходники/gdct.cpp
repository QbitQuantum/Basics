int GDCT_Transfer::do_connect_svr()
{
	ACE_SOCK_Connector conn;
	ACE_INET_Addr addr(svr_port_,svr_ip_.c_str());
	ACE_Time_Value to = default_timeout_;
	if(conn.connect(connector_,addr,&default_timeout_)!=0)
	{
		int r = ACE_OS::last_error();
		ACE_DEBUG((LM_ERROR,"连接讯源服务器失败[%s:%d]ret[%d:%s]",svr_ip_.c_str(),svr_port_,
			r,ACE_OS::strerror(r)));
		return -1;
	}
	ACE_DEBUG((LM_INFO,"连接讯源服务器成功[%s:%d]",svr_ip_.c_str(),svr_port_));
	is_connected_ = 1;
	return 0;
}