static void connected(const boost::system::error_code & ec, boost::asio::ip::tcp::socket & msocket)
{
	if ( ec )
		std::cout <<  ec.message() <<  std::endl;
	else
		msocket.write_some(boost::asio::buffer(std::string("GET / HTTP/1.1\r\n\r\n")));
}