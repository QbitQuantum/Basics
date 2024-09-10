	void dht_tracker::start(entry const& bootstrap)
	{
		std::vector<udp::endpoint> initial_nodes;

		if (bootstrap.type() == entry::dictionary_t)
		{
			try
			{
			if (entry const* nodes = bootstrap.find_key("nodes"))
				read_endpoint_list<udp::endpoint>(nodes, initial_nodes);
			} catch (std::exception&) {}
		}

		error_code ec;
		m_timer.expires_from_now(seconds(1), ec);
		m_timer.async_wait(bind(&dht_tracker::tick, self(), _1));

		m_connection_timer.expires_from_now(seconds(10), ec);
		m_connection_timer.async_wait(
			bind(&dht_tracker::connection_timeout, self(), _1));

		m_refresh_timer.expires_from_now(seconds(5), ec);
		m_refresh_timer.async_wait(bind(&dht_tracker::refresh_timeout, self(), _1));

		m_dht.bootstrap(initial_nodes, boost::bind(&dht_tracker::on_bootstrap, self()));
	}