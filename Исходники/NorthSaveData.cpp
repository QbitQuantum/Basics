// get our Citizen save game directory
static std::wstring GetCitizenSavePath()
{
	PWSTR saveBasePath;

	// get the 'Saved Games' shell directory
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SavedGames, 0, nullptr, &saveBasePath)))
	{
		// create a STL string and free the used memory
		std::wstring savePath(saveBasePath);

		CoTaskMemFree(saveBasePath);

		// append our path components
		AppendPathComponent(savePath, L"\\CitizenFX");
		AppendPathComponent(savePath, L"\\GTA4");

		// append a final separator
		savePath += L"\\";

		// and return the path
		return savePath;
	}

	return GetOriginalSavePath();
}