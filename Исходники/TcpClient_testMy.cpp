void connectCallback( const TcpConnectionPtr& conn)
{
	LOG_INFO << "-----------connectionCallback";
	string msg = "a";

	conn->send(msg);
 

}