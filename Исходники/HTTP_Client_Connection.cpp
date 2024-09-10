void
HTTP_Client_Connection::on_write_some(ACE_Message_Block& mb, size_t bytes_transferred)
{
	// keep writing
	if ( mb.length() > 0 )
	{
		this->write(mb);
		return;
	}
	// write completed
	else
	{
		buf_.resize(0);

		mb.reset();
		this->read(mb);
	}	
}