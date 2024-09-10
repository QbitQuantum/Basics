wstring CFileSystemServiceImpl::makeValidPath(const wstring& path1) {
	wstring path = path1;
	size_t p = path.find(L'%');
	while (p != wstring::npos) {
		size_t e = path.find(L'%', p+1);
		if (e == wstring::npos) break;
		wstring variableName = path.substr(p+1, e-p-1);
		wstring variableValue = getenv(variableName);
		replaceStringInPlace(path, path.substr(p, e+1-p), variableValue);
		p = path.find(L'%');
	}

	p = path.find(L'{');
	while (p != wstring::npos) {
		size_t e = path.find(L'}', p+1);
		if (e == wstring::npos) break;
		wstring variableName = path.substr(p, e-p+1);
		GUID guid;
		if (CLSIDFromString(variableName.c_str(), &guid) == S_OK) {
			LPWSTR folderPath = NULL;
			SHGetKnownFolderPath(guid, 0, NULL, &folderPath);
			if (folderPath) {
				replaceStringInPlace(path, path.substr(p, e+1-p), folderPath);
				CoTaskMemFree(folderPath);
			}
		}
		p = path.find(L'{');
	}		

	return path;
}