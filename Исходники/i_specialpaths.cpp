bool GetKnownFolder(int shell_folder, REFKNOWNFOLDERID known_folder, bool create, FString &path)
{
	using OptWin32::SHGetFolderPathA;
	using OptWin32::SHGetKnownFolderPath;

	char pathstr[MAX_PATH];

	// SHGetKnownFolderPath knows about more folders than SHGetFolderPath, but is
	// new to Vista, hence the reason we support both.
	if (!SHGetKnownFolderPath)
	{
		// NT4 doesn't even have this function.
		if (!SHGetFolderPathA)
			return false;

		if (shell_folder < 0)
		{ // Not supported by SHGetFolderPath
			return false;
		}
		if (create)
		{
			shell_folder |= CSIDL_FLAG_CREATE;
		}
		if (FAILED(SHGetFolderPathA(NULL, shell_folder, NULL, 0, pathstr)))
		{
			return false;
		}
		path = pathstr;
		return true;
	}
	else
	{
		PWSTR wpath;
		if (FAILED(SHGetKnownFolderPath(known_folder, create ? KF_FLAG_CREATE : 0, NULL, &wpath)))
		{
			return false;
		}
		// FIXME: Support Unicode, at least for filenames. This function
		// has no MBCS equivalent, so we have to convert it since we don't
		// support Unicode. :(
		bool converted = false;
		if (WideCharToMultiByte(GetACP(), WC_NO_BEST_FIT_CHARS, wpath, -1,
			pathstr, countof(pathstr), NULL, NULL) > 0)
		{
			path = pathstr;
			converted = true;
		}
		CoTaskMemFree(wpath);
		return converted;
	}
}