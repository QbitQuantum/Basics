void CassandraConnectionChannel::read_size_handler(const boost::system::error_code& error, std::size_t bytes_transferred, std::size_t bytes_to_read,  apache::thrift::transport::TMemoryBuffer* message, const VoidCallback& cob){
  updateTimerContext();
  if (error){
    handleError(error);
    return;
  }

  settimer(m_IOTimeoutms);
  
  bytes_to_read -= bytes_transferred;
  if (!bytes_to_read){
    //we are done, read the message itself
    m_Insize = ntohl(m_Insize);
    uint8_t* bufPtr = message->getWritePtr(m_Insize);
    

    m_Socket.async_read_some(boost::asio::buffer(bufPtr, m_Insize),
			     boost::bind(& CassandraConnectionChannel::read_message_handler, 
					shared_from_this(), 
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred,
					m_Insize,
					message,
					cob));
    return;
  }

  //need to read more
  uint8_t* bufPtr = reinterpret_cast<uint8_t*>(&m_Insize);
  bufPtr+= (4-bytes_to_read);
  m_Socket.async_read_some(boost::asio::buffer(bufPtr, bytes_to_read),
			   boost::bind(& CassandraConnectionChannel::read_size_handler, 
					shared_from_this(), 
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred,
					bytes_to_read,
				        message,
					cob));
}