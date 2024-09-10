void UdpClient::onSend( const string& message, const boost::system::error_code& error, 
	std::size_t bytesTransferred )
{
	OutputDebugStringA( ( error.message() + "\n" ).c_str() );
}