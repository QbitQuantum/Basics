		CommandExecutionResults StoreTextCommand::Execute(const ExecutionContext& context)
		{
			auto& currentDir = GetCurrentPath(this->context->UserData, context.Message->SourceProtocol, context.Message->Sender);
			auto& content = context.ParseResults->GetParameter("content");
			auto path = SanitizePath(context.ParseResults->GetParameter("file"));
			auto newPath = JoinPath(currentDir, path);
			if (newPath.empty())
			{
				throw Exceptions::ExecutionException(InvalidPath);
			}
			if (PathIsDirectoryA(newPath.c_str()))
			{
				throw Exceptions::ExecutionException(PathIsNotFile);
			}

			std::ofstream file(newPath, std::ios_base::binary | std::ios_base::trunc);
			file.write(content.c_str(), content.size());
			if (!file)
			{
				throw Exceptions::ExecutionException(CannotWriteToFile);
			}
			return CommandExecutionResults(FileWritten);
		}