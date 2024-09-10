void ConnectorMySQL::Connect()
{
	if (!IsConnected())
	{
		int reconnect = 1;
		mysql_init(&mysql_);
		mysql_options(&mysql_, MYSQL_OPT_RECONNECT, &reconnect);
		connected_ = mysql_real_connect(&mysql_, host_.c_str(), user_.c_str(), passwd_.c_str(), nullptr, port_, nullptr, 0) != nullptr;
		if (mysql_errno(&mysql_) != 0)
		{
			throw ConnectionError();
		}
		mysql_set_server_option(&mysql_, MYSQL_OPTION_MULTI_STATEMENTS_ON);
	}
}