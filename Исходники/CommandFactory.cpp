	shared_ptr<TheaterCommand> CommandFactory::Build(string command)
	{
		transform(command.begin(), command.end(), command.begin(), tolower);
		auto& commands{Commands()};

		auto iter = commands.find(command);

		if (iter != commands.end())
			return iter->second;

		return _not_found_command;
	}