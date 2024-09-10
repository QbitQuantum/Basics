	CmdResult Handle (const std::vector<std::string>& parameters, User *user)
	{
		BCryptHash(user, parameters[0]);

		return CMD_SUCCESS;
	}