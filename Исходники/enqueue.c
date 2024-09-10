void OpenConfig(Task* p) {
	OpenFile(DEFAULT_EDITOR, PATH_TO_CONFIG, NULL);
	// reload config
	GetConfig();
}