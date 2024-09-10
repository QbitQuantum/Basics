void http_connect_handler(http_connection& c)
{
	++connect_handler_called;
	TEST_CHECK(c.socket().is_open());
	error_code ec;
	std::cerr << time_now_string() << " connected to: " << print_endpoint(c.socket().remote_endpoint(ec))
		<< std::endl;
// this is not necessarily true when using a proxy and proxying hostnames
//	TEST_CHECK(c.socket().remote_endpoint(ec).address() == address::from_string("127.0.0.1", ec));
}