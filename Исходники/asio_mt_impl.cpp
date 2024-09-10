	// read_callback - passed information about bytes in read_buf to handle_by_protocol method.	
	void read_callback(size_t bytes_transferred,const system::error_code& error)
	{
		if (error || !bytes_transferred)
		{
			if(log_level) std::cerr << "read callback error:" << error << ": " << error.message() << std::endl;
			return;
		}

		long packet_found = data_received(read_buf,bytes_transferred);
		if(!packet_found) {
			initiate_read();
		}
	}