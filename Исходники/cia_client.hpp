void cia_client::stop()
{
	if (!m_started_) return;
	m_started_ = false;
	m_sock_.close();
	m_deal_ch_msg_group.interrupt_all();

	ptr self = shared_from_this();
	auto it = std::find(clients.begin(), clients.end(), self);
	clients.erase(it);
	BOOST_LOG_SEV(cia_g_logger, Debug) << "客户端socket已经调用stop函数关闭";
	//x m_config_server->set_started(true);	// 为了防止网络情况异常, 造成服务端关闭连接后重置此值为2, 通讯端保证此值为1
}