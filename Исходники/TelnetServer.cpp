void TelnetServer::start( int port )
{
	Socket::Address addr( port );
	mSocket.bind( addr );
	mSocket.listen( 5 );
	mSocket.setSelector( this, &mSelector );
}