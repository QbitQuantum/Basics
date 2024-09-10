WindowsFilesystemNode::WindowsFilesystemNode(const Common::String &p, const bool currentDir) {
	if (currentDir) {
		char path[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, path);
		_path = path;
	} else {
		assert(p.size() > 0);
		_path = p;
	}

	_displayName = lastPathComponent(_path, '\\');

	// Check whether it is a directory, and whether the file actually exists
	DWORD fileAttribs = GetFileAttributes(toUnicode(_path.c_str()));

	if (fileAttribs == INVALID_FILE_ATTRIBUTES) {
		_isDirectory = false;
		_isValid = false;
	} else {
		_isDirectory = ((fileAttribs & FILE_ATTRIBUTE_DIRECTORY) != 0);
		_isValid = true;
		// Add a trailing slash, if necessary.
		if (_isDirectory && _path.lastChar() != '\\') {
			_path += '\\';
		}
	}
	_isPseudoRoot = false;
}