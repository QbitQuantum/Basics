void server_conn::output_error( std::string err_msg, const boost::system::error_code &e )
{
	cerr<<err_msg<<", error message: "<<e.message()<<endl;
}