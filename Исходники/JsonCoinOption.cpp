	CJsonCoinOption(const std::string& filepath)
	{
		try
		{
			Json::Value jsv = json_from_file(filepath);
			if (jsv.empty())
			{
				m_is_error = true;
				return;
			}
			this->prev_name = jsv["Name"].asString();
			Json::Value& dnslist = jsv["DnsList"];
			for (auto it = dnslist.begin(); it != dnslist.end(); ++it)
			{
				Json::Value& v = *it;
				this->DNSSeed.push_back(v.asString());
			}
			std::string szNetHead = jsv["NetHead"].asString();
			binary bNetHead = from_hex(szNetHead.c_str());
			if (bNetHead.size() == 4)
			{
				this->pchMessageStart[0] = bNetHead[0];
				this->pchMessageStart[1] = bNetHead[1];
				this->pchMessageStart[2] = bNetHead[2];
				this->pchMessageStart[3] = bNetHead[3];
			}
			this->port = jsv["NetPort"].asInt();
			this->protocol_version = jsv["NetVersion"].asInt();
			this->first_blockhash = rstr_to_uint256(jsv["first_block_hash"].asString());
			this->first_blocktime = jsv["first_block_time"].asInt();
			if ((int)this->first_blocktime < 0)
			{
				this->first_blocktime = _time32(0) + int(this->first_blocktime);
			}
			this->PubkeyStart = jsv["Pubkey_Start"].asInt();

			m_is_error = false;
		}
		catch(std::exception& e)
		{
			printf("%s\n", e.what());
			m_is_error = true;
		}
	}