	virtual void SetUp()
	{
		using namespace boost::asio;
		using boost::bind;

		TimedSessionBase::SetUp();

		session_channel = 0;
		user_message = beep::message();

		netchng = transport.install_network_handler(bind(&SessionListener::handle_transport_connect,
														 this, _1, _2));

		listener.install_profile("casimiro.daniel/test-profile",
								 bind(&SessionListener::handle_test_profile_change,
									  this, _1, _2, _3, _4));

		ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 9999);
		transport.set_endpoint(ep);
		transport.start_listening();
		socket.async_connect(ep, bind(&SessionListener::handle_connect, this,
									  placeholders::error));
		ASSERT_NO_THROW(run_event_loop_until_connect());
		ASSERT_TRUE(socket.is_open());
		// wait for the greeting message
		ASSERT_NO_THROW(run_event_loop_until_frame_received());
	}