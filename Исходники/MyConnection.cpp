///Metoda wołana przy odbieraniu danych
void MyConnection::OnRecv( std::vector< uint8_t > & buffer )
{
	global_stream_lock.lock();
	std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes" << std::endl;
	for( size_t x = 0; x < buffer.size(); ++x )
	{
		std::cout <<(char)buffer[ x ] << " ";
		if( ( x + 1 ) % 16 == 0 )
		{
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	global_stream_lock.unlock();
	Recv();
	p->SigW(NET,&buffer);
	//p->work(nullptr);
	// Start the next receive


	// Echo the data back
	//Send( buffer ); TODO: send ACK to server??
}