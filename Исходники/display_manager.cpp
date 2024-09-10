bool DisplayManager::setGraphicsMode(const char *name) {
	DEBUG_ENTER_FUNC();

	int i = 0;

	while (_supportedModes[i].name) {
		if (!strcmpi(_supportedModes[i].name, name)) {
			setGraphicsMode(_supportedModes[i].id);
			return true;
		}
		i++;
	}

	return false;
}