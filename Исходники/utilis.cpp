void FileLogAppender::setLogDirectory(std::wstring const &directory) {
	logFilePath_ = directory;
	createLogFile();
}