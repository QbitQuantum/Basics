bool ConfigManager::save() {
	if (!_config)
		return true;

	if (!getBool("saveconf", true))
		return true;

	// Create the directories in the path, if necessary
	UString file = FilePath::canonicalize(getConfigFile());

	try {
		FilePath::createDirectories(FilePath::getDirectory(file));

		// Open and save the config
		WriteFile config;
		if (!config.open(file))
			throw Exception(kOpenError);

		save(config, true);

	} catch (...) {
		exceptionDispatcherWarning("Failed saving config file \"%s\"", file.c_str());
		return false;
	}

	return true;
}