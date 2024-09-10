bool GameInstanceEngine::probe() {
	if (Common::FilePath::isDirectory(_target)) {
		// Try to probe from that directory

		Common::FileList rootFiles;

		if (!rootFiles.addDirectory(_target))
			// Fatal: can't read the directory
			return false;

		return probe(rootFiles);
	}

	if (Common::FilePath::isRegularFile(_target)) {
		// Try to probe from that file

		Common::ReadFile file;
		if (file.open(_target))
			return probe(file);
	}

	return false;
}