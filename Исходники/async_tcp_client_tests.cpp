				void send()
				{
					BOOST_CHECK_EQUAL( socket_.is_open(), true );
					size_t l = 5;
					socket_.send( boost::asio::buffer( &l, sizeof(size_t) ) );
					socket_.send( boost::asio::buffer( "hello", 5 ) );
				}