void EnumDir(CStringA resToken, int nEnumSubdir, std::vector<CString>& vecFiles)
{
	int nEndSlash = resToken.ReverseFind('\\');
	if (nEndSlash == -1)
		return;

	USES_CONVERSION;

	CStringA path = resToken.Mid(0, nEndSlash);
	CStringA findname = resToken.Mid(nEndSlash + 1);

	// file
	WIN32_FIND_DATAA fd;
	memset(&fd, 0, sizeof(WIN32_FIND_DATAA));
	HANDLE hFind = FindFirstFileA(resToken, &fd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			CStringA subname = fd.cFileName;
			if (subname != "." && subname != "..")
			{
				CStringA fname = path + "\\" + subname;
				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
				}
				else
					vecFiles.push_back(A2CT(fname));
			}
		} while (FindNextFileA(hFind, &fd) != 0);

		FindClose(hFind);
	}

	// directory
	if (nEnumSubdir > 0)
	{
		hFind = FindFirstFileA(path + "\\*.*", &fd);

		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				CStringA subname = fd.cFileName;
				if (subname != "." && subname != "..")
				{
					CStringA fname = path + "\\" + subname;
					if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
						EnumDir(fname + "\\" + findname, nEnumSubdir, vecFiles);
				}
			} while (FindNextFileA(hFind, &fd) != 0);

			FindClose(hFind);

		}
	}
}