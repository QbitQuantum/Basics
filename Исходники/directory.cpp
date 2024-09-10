void
Directory::scan() {
	reset();

	Poco::DirectoryIterator dirIt(_directoryPath);
	Poco::DirectoryIterator dirEnd;
	for (; dirIt != dirEnd; ++dirIt) {
		if (dirIt->isFile()) {
			File* foundFile = new File(*dirIt);
			_files.push_back(foundFile);
		} else if (dirIt->isDirectory()) {
			Directory* foundDir = new Directory(*dirIt);
			foundDir->scan();
			_subDirectories.push_back(foundDir);
		} else {
			TITANIC_WARN(Log, "Object is not a file or directory [" << dirIt->path() << "]");
		}
	}

}