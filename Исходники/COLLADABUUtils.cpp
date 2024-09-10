	//--------------------------------
	bool Utils::createDirectoryRecursive( const WideString &pathString )
	{
		if (pathString.length() == 0)
			return false;

		WideString path = pathString;

		if (path[path.length()-1] != '/' && path[path.length()-1] != '\\')
			path.push_back('\\');

		std::list<WideString> paths;
		size_t offset = WideString::npos;
		while ((offset != 0) && (offset = pathString.find_last_of(L"/\\", offset)) != WideString::npos)
		{
			paths.push_front(pathString.substr(0, offset + 1));
			if (offset != 0) --offset;
		}

		bool pathExists = true;
		const wchar_t* currentPath = _wgetcwd(0, 0);

		for (std::list<WideString>::const_iterator iPath = paths.begin(); iPath != paths.end(); ++iPath)
		{
			// if path exists
			if (_wchdir((*iPath).c_str()) == 0)
				continue;

			// path does not exist, try to create it
			_wmkdir((*iPath).c_str());
			
			if (_wchdir((*iPath).c_str()) != 0)
			{
				pathExists = false;
				break;
			}
		}

		// Restore current path
		_wchdir(currentPath);
		return pathExists;
	}