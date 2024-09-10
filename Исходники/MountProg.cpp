bool CMountProg::GetPath(char **returnPath)
{
	unsigned long i, nSize;
	static char path[MAXPATHLEN + 1];
	static char finalPath[MAXPATHLEN + 1];
	bool foundPath = false;

	m_pInStream->Read(&nSize);

	if (nSize > MAXPATHLEN) {
		nSize = MAXPATHLEN;
	}

	typedef std::map<std::string, std::string>::iterator it_type;
	m_pInStream->Read(path, nSize);

	for (it_type iterator = m_PathMap.begin(); iterator != m_PathMap.end(); iterator++) {
		char* pathAlias = const_cast<char*>(iterator->first.c_str());
		char* windowsPath = const_cast<char*>(iterator->second.c_str());

		size_t aliasPathSize = strlen(pathAlias);
		size_t windowsPathSize = strlen(windowsPath);
		size_t requestedPathSize = nSize;

		if ((requestedPathSize < windowsPathSize) && (strncmp(path, pathAlias, aliasPathSize) == 0)) {
			foundPath = true;
			//The requested path starts with the alias. Let's replace the alias with the real path
			strncpy_s(finalPath, windowsPath, sizeof(finalPath));
			//strncpy_s(finalPath + windowsPathSize, (path + aliasPathSize), (sizeof(finalPath)-windowsPathSize));
			finalPath[windowsPathSize + requestedPathSize - aliasPathSize] = '\0';

			for (i = 0; i < requestedPathSize; i++) { //transform path to Windows format
				if (finalPath[windowsPathSize + i] == '/') {
					finalPath[windowsPathSize + i] = '\\';
				}
			}
		} else if ((strlen(path) == strlen(pathAlias)) && (strncmp(path, pathAlias, aliasPathSize) == 0)) {
			foundPath = true;
			//The requested path IS the alias
			strncpy_s(finalPath, windowsPath, sizeof(finalPath));
			finalPath[windowsPathSize] = '\0';
		} else if ((strlen(path) == strlen(windowsPath)) && (strncmp(path, pathAlias, windowsPathSize) == 0)) {
			foundPath = true;
			//The requested path does not start with the alias, let's treat it normally
			strncpy_s(finalPath, path, sizeof(finalPath));
			finalPath[0] = finalPath[1];  //transform mount path to Windows format
			finalPath[1] = ':';

			for (i = 2; i < nSize; i++) {
				if (finalPath[i] == '/') {
					finalPath[i] = '\\';
				}
			}

			finalPath[nSize] = '\0';
		}

		if (foundPath == true) {
			break;
		}
	}

	PrintLog("Final local requested path: %s\n", finalPath);

	if ((nSize & 3) != 0) {
		m_pInStream->Read(&i, 4 - (nSize & 3));  //skip opaque bytes
	}

	*returnPath = finalPath;
	return foundPath;
}