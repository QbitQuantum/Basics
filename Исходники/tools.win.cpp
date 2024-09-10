std::string et::documentsBaseFolder()
{
	wchar_t* path = nullptr;
	SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &path);

	if (path == nullptr) 
		return std::string();

	std::string result = addTrailingSlash(unicodeToUtf8(path));
	CoTaskMemFree(path);
	return result;
}