	//接受新的请求
	void accept_handler(const system::error_code& e, sock_ptr s)
	{
		if (e)
		{
			cout << e.message() << endl;
			return;
		}
		//添加
		clientSock.push_back(s);
		cout << "client:" << s->remote_endpoint().address() << " port:" << s->remote_endpoint().port() << endl;
		
		s->async_write_some(buffer("hello asio"), boost::bind(&server::write_handle, this, boost::asio::placeholders::error, s));
		//继续异步请求
		start();
	}