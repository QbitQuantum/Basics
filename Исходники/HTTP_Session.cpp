int
HTTP_SSL_Client_Session::on_read_complete(ACE_Message_Block& mb, const TRB_Asynch_Read_Stream::Result& result)
{
	ACE_OS::write_n(ACE_STDOUT, mb.rd_ptr(), mb.length()); //@

	//static int i = 0;
	//::printf("%d, ", i++);

	return 0;
}