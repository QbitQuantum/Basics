void connect_host(Socket &s,
	tcp::resolver::iterator &endpoint_iterator, boost::system::error_code &ec)
{
	tcp::resolver::iterator end;
	// 尝试连接解析出来的代理服务器地址.
	ec = boost::asio::error::host_not_found;
	while (ec && endpoint_iterator != end)
	{
		s.close(ec);
		s.connect(*endpoint_iterator++, ec);
	}
}