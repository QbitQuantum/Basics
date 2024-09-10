bool CPanasonicNode::handleConnect(boost::asio::ip::tcp::socket& socket, boost::asio::ip::tcp::endpoint endpoint, boost::system::error_code& ec)
{
	try
	{
		if (!m_stoprequested)
		{
			socket.connect(endpoint, ec);
			if (!ec)
			{
				if (DEBUG_LOGGING) _log.Log(LOG_NORM, "Panasonic Plugin: (%s) Connected to '%s:%s'.", m_Name.c_str(), m_IP.c_str(), (m_Port[0] != '-' ? m_Port.c_str() : m_Port.substr(1).c_str()));
				return true;
			}
			else
			{
				if (DEBUG_LOGGING)
					if (((ec.value() != 113) && (ec.value() != 111) &&
						(ec.value() != 10060) && (ec.value() != 10061) && (ec.value() != 10064) && (ec.value() != 10061))) // Connection failed due to no response, no route or active refusal
					_log.Log(LOG_NORM, "Panasonic Plugin: (%s) Connect to '%s:%s' failed: (%d) %s", m_Name.c_str(), m_IP.c_str(), (m_Port[0] != '-' ? m_Port.c_str() : m_Port.substr(1).c_str()), ec.value(), ec.message().c_str());
				return false;
			}
		}
	}
	catch (std::exception& e)
	{
		_log.Log(LOG_ERROR, "Panasonic Plugin: (%s) Exception: '%s' connecting to '%s'", m_Name.c_str(), e.what(), m_IP.c_str());
		return false;
	}

	return true;

}