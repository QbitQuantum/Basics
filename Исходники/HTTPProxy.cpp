	void HTTPProxyHandler::SentHTTPFailed(const boost::system::error_code & ecode)
	{
		if (!ecode)
			Terminate();
		else 
		{
			LogPrint (eLogError,"--- HTTP Proxy Closing socket after sending failure because: ", ecode.message ());
			Terminate();
		}
	}