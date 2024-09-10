		CommandExecutionResults CatCommand::Execute(const ExecutionContext& context)
		{
			auto& currentDir = GetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender);
			std::string path = SanitizePath(context.ParseResults->GetParameter("file"));
			std::string newPath = JoinPath(currentDir, path);
			if (newPath.empty())
			{
				throw Exceptions::ExecutionException(InvalidPath);
			}
			if (PathIsDirectoryA(newPath.c_str()))
			{
				throw Exceptions::ExecutionException(PathIsNotFile);
			}
			if (!PathFileExistsA(newPath.c_str()))
			{
				throw Exceptions::ExecutionException(FileDoesNotExist);
			}

			std::ifstream file(newPath, std::ios_base::binary);
			file.seekg(0, std::ios_base::end);
			int64_t length = file.tellg();
			file.seekg(0, std::ios_base::beg);
			if (length == -1 || !file)
			{
				throw Exceptions::ExecutionException(CannotReadFile);
			}
			if (length > MaxFileLength)
			{
				length = MaxFileLength;
			}

			std::unique_ptr<char[]> buffer(new char[(unsigned)length + 1]);
			if (file.read(buffer.get(), length).bad())
			{
				throw Exceptions::ExecutionException(CannotReadFile);
			}
			buffer.get()[length] = 0;
			return CommandExecutionResults(std::string(buffer.get()));
		}