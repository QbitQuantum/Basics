	ModResult AccessCheck(User* source, Channel* channel, std::string &parameter, bool adding)
	{
		std::string::size_type pos = parameter.find(':');
		if (pos == 0 || pos == std::string::npos)
			return adding ? MOD_RES_DENY : MOD_RES_PASSTHRU;
		unsigned int mylevel = channel->GetPrefixValue(source);
		std::string mid = parameter.substr(0, pos);
		ModeHandler* mh = FindMode(mid);

		if (adding && (!mh || !mh->GetPrefixRank()))
		{
			source->WriteNumeric(415, "%s %s :Cannot find prefix mode '%s' for autoop",
				source->nick.c_str(), mid.c_str(), mid.c_str());
			return MOD_RES_DENY;
		}
		else if (!mh)
			return MOD_RES_PASSTHRU;

		std::string dummy;
		if (mh->AccessCheck(source, channel, dummy, true) == MOD_RES_DENY)
			return MOD_RES_DENY;
		if (mh->GetLevelRequired() > mylevel)
		{
			source->WriteNumeric(482, "%s %s :You must be able to set mode '%s' to include it in an autoop",
				source->nick.c_str(), channel->name.c_str(), mid.c_str());
			return MOD_RES_DENY;
		}
		return MOD_RES_PASSTHRU;
	}