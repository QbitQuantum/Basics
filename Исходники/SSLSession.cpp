void SSLSession::handle_handshake(const boost::system::error_code& error)
{
	if (error)
	{
		gFileLog::instance().Log("SSLSession 握手失败， 错误代码:" + boost::lexical_cast<std::string>(error.value()) + ", 错误消息:" + error.message());

		close();
		return;
	}	
	
	read();
}