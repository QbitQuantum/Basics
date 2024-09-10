	AuthModule* AuthModule::loadFromName(std::string name)
	{
		int length;
		char* filename;
		char* lowerName;
		std::string libraryPath;
		AuthModule* module;
		pRdsAuthModuleEntry moduleEntry;

		libraryPath = APP_CONTEXT.getLibraryPath();

		lowerName = _strdup(name.c_str());
		CharLowerA(lowerName);

		length = strlen(lowerName) + libraryPath.size() + 64;
		filename = (char*) malloc(length + 1);

		sprintf_s(filename, length, "%s/libfreerds-auth-%s.so", libraryPath.c_str(), lowerName);
		free(lowerName);

		module = AuthModule::loadFromFileName(filename);

		free(filename);

		return module;
	}