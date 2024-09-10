	virtual void send(raw_data& data) {
		bool write_in_progress = !buffer_write_queue_.empty();
		buffer_write_queue_.push_back(data);
		if (!write_in_progress) {
			socket_.async_write_some(
					boost::asio::buffer(buffer_write_queue_.front().bytes, buffer_write_queue_.front().length),
					boost::bind(&session::handle_write, shared_from_this(),
							boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
	}