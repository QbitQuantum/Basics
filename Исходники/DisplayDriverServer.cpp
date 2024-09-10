	PrivateData( int portNumber ) :
		m_success(false),
		m_endpoint(tcp::v4(), portNumber),
		m_service(),
		m_acceptor( m_service ),
		m_thread()
	{
		m_acceptor.open(  m_endpoint.protocol() );
		m_acceptor.set_option( boost::asio::ip::tcp::acceptor::reuse_address(true));
		m_acceptor.bind( m_endpoint );
		m_acceptor.listen();
		m_success = true;
	}