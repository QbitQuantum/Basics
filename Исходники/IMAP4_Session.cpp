int
IMAP4_SSL_Client_Session::on_write_complete(ACE_Message_Block& mb, const TRB_Asynch_Write_Stream::Result& result)
{
	//ACE_Time_Value tv(0, 10 * 1000);
	//timespec_t t  = (timespec_t) tv;
	//ACE_OS::nanosleep(&t);

	ACE_OS::write_n(ACE_STDOUT, mb.rd_ptr(), mb.length()); //@

	ACE_Message_Block* mb_read = new (std::nothrow) ACE_Message_Block(BUFSIZE+1);
	if ( !mb_read ) return -1;
	if ( read(*mb_read) != 0 ) return -1;

	// initialize a new read
	++step_;
	io_.read_reset();

	return 0;
}