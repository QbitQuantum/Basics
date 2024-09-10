		void	startRead()
		{
			checkNotReading(true);
			 
			reading = true;
			readBuff.ensure_write_space(MAX_READ_BYTES_ONCE);
			socket.async_read_some(boost::asio::buffer(readBuff.wt_ptr(), readBuff.writeable_bytes()),
				boost::bind(&TcpConnection::handleRead, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}