bool comm_link::is_connection_error(exception_ptr const& _exception)
{
	try
	{
		rethrow_exception(_exception);
		BOOST_ASSERT(false);
	}
	catch(system_error& e)
	{
		if(e.code() == boost::system::errc::message_size)
			return false;

		return true;
	}
	catch(...)
	{}
	return false;
}