/*************************************************************************
 * SHGetFolderPathW			[SHELL32.@]
 */
HRESULT WINAPI SHGetFolderPathW(
	HWND hwndOwner,
	int nFolder,
	HANDLE hToken,
	DWORD dwFlags,
	LPWSTR pszPath)
{
	return (SHGetSpecialFolderPathW(
		hwndOwner,
		pszPath,
		CSIDL_FOLDER_MASK & nFolder,
		CSIDL_FLAG_CREATE & nFolder )) ? S_OK : E_FAIL;
}