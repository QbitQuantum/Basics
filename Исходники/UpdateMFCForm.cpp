//this should only be called if an update is needed.
UINT __stdcall InstallFilesThread(void *form)
{
	UpdateForm* temp = static_cast<UpdateForm*>(form);

	if (!temp)
	{
		::MessageBox(NULL, "Failed to find update form!", "Desura: ERROR", MB_OK);
		exit(-1);
	}

	while (!temp->isInit())
		gcSleep(500);

	if (FileExists(L"update_lock.txt"))
	{
		DWORD ret = ::MessageBox(temp->GetSafeHwnd(), "It looks like Desura tried to update and failed. Want to try again?", "Desura", MB_YESNO);
		DeleteFileW(L"update_lock.txt");

		if (ret == IDNO)
		{
			temp->EndDialog(2);
			return 2;
		}
	}

	FILE* fh = Safe::fopen("update_lock.txt", "wb");

	if (fh)
		fclose(fh);


	UINT res = DownloadAndInstallMCF(temp);


	DeleteFile("update_lock.txt");

	temp->EndDialog(res);
	return res;
}