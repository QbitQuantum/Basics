	void p2p_connection::handle_read_body(const boost::system::error_code& error)
	{
		if (!error)
		{
			size_t bodyLength = packet_.body_length();
			// if this is a single byte ping packet, ping back, or just ignore if it's a reply.
			if (bodyLength == 1)
			{
				unsigned char ping = packet_.body()[0];
				if (ping == 0)
				{
					unsigned char ping[1];
					ping[0] = 1;
					Send(ping, 1);
				}
			}
			else
			{
			  if (_remoteId == "")
			  {
				  std::string body(packet_.body(), packet_.body() + bodyLength);
				  _remoteId = body.substr(0, bodyLength);
				  if (_localId != _remoteId)
				  {
					  NodeConnected(isIncoming_, shared_from_this(), _remoteId);

					  std::stringstream id_stream;
					  id_stream << _localId;

					  if (isIncoming_)
						  Send(std::string(id_stream.str()));
				  }
				  else
				  {
					  std::stringstream ss;
					  ss << "Dropped connection to self. " << socket_.remote_endpoint();
					  Log(std::string(ss.str()));

					  //socket_.shutdown(boost::asio::socket_base::shutdown_both);
					  //_io_service.stop();
					  return;
				  }
			  }
			  else
				  ReceivedData(shared_from_this(), packet_);
			}
			
			if (write_queue_.empty())
			{
				// todo: this would be better if it continually checked for 3 secs if theres any queued outgoing,
				// if any appear, it continues, if not, it pings 
				// (or else we have to wait until the next round to send) up to 3 secs of potential lag with thread::sleep method
				boost::this_thread::sleep(boost::posix_time::milliseconds(3000));

				unsigned char ping[1];
				ping[0] = 0;
				Send(ping, 1);
			}

			boost::asio::async_write(socket_,
   									 boost::asio::buffer(write_queue_.front().data(),
									 write_queue_.front().length()),
									 boost::bind(&p2p_connection::handle_write, shared_from_this(),
									 boost::asio::placeholders::error));
		}
		else
		{
			// we got disconnected or sumfin
			if (error)
				NodeDisconnected(_remoteId, std::string("(handle_read_body) ").append(error.message()));
			else
				NodeDisconnected(_remoteId, "(handle_read_body) no error");
		}
	}