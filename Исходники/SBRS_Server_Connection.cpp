void
SBRS_Server_Connection::write(ACE_Message_Block& mb, long timeout)
{
	ACE_GUARD(ACE_Thread_Mutex, guard, lock_);

	socket_.async_write_some(buffer(mb.rd_ptr(), mb.length()), strand_.wrap(boost::bind(
		&SBRS_Server_Connection::handle_write,
		this,
		placeholders::error,
		placeholders::bytes_transferred)));

	if ( timeout > 0 )
	{
		timer_.expires_from_now(boost::posix_time::seconds(timeout));
		timer_.async_wait(strand_.wrap(boost::bind(
			&SBRS_Server_Connection::handle_socket_timeout,
			this,
			placeholders::error)));
	}
}