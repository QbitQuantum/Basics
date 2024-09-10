	std::shared_ptr<FileInterface> FileCommand::Create(const char *command, const char *mode)
	{
		std::shared_ptr<FileInterface> returnValue;
		assert(command != nullptr && mode != nullptr && "Invalid string");
		FILE *file = _popen(command, mode);
		if (file)
		{
			returnValue.reset(new FileCommand(command, file));
		}
		return returnValue;
	}