int CFolderItem::FolderDeleteOldDirectory(int showFolder)
{
	int res = FOLDER_SUCCESS;
	if (IsUnicode())
		{
			wchar_t buffer[MAX_FOLDER_SIZE];
			if (szOldFormatW)
				{
					if (wcscmp(szFormatW, szOldFormatW) == 0) //format wasn't changed
						{
							return res;
						}
					ExpandPathW(buffer, szOldFormatW, MAX_FOLDER_SIZE);
					RemoveDirectories(buffer);
					res = (DirectoryExists(buffer)) ? FOLDER_FAILURE : FOLDER_SUCCESS;
					if ((res == FOLDER_FAILURE) && (showFolder))
						{
							ShellExecuteW(NULL, L"explore", buffer, NULL, NULL, SW_SHOW);
						}
				}
		}
		else{
			char buffer[MAX_FOLDER_SIZE];
			if (szOldFormat)
				{
					if (strcmp(szFormat, szOldFormat) == 0) //format wasn't changed
						{
							return res;
						}
					ExpandPath(buffer, szOldFormat, MAX_FOLDER_SIZE);
					RemoveDirectories(buffer);
					res = (DirectoryExists(buffer)) ? FOLDER_FAILURE : FOLDER_SUCCESS;
					if ((res == FOLDER_FAILURE) && (showFolder))
						{
							ShellExecuteA(NULL, "explore", buffer, NULL, NULL, SW_SHOW);
						}
				}
		}
	return res;
}