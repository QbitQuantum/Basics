UINT DownloadAndInstallMCF(UpdateForm* temp)
{
	UMcfEx *updateMcf = new UMcfEx();
	updateMcf->onProgressEvent += delegate(temp, &UpdateForm::onProgressN);
	updateMcf->onDownloadProgressEvent += delegate(temp, &UpdateForm::onProgressD);

	DeleteFile(UPDATEXML);

	std::wstring path = UTIL::OS::getAppDataPath(L"dumps\0\0");

	SHFILEOPSTRUCTW lpFileOp;
	lpFileOp.wFunc = FO_DELETE;
	lpFileOp.pFrom = path.c_str();
	lpFileOp.pTo = NULL;
	lpFileOp.hwnd = NULL;
	lpFileOp.fFlags = (FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR);
	SHFileOperationW(&lpFileOp);

#ifndef DEBUG
	temp->getProgressControl()->setMode(MODE_DOWNLOADING);

	try
	{
		updateMcf->getUpdateInfo(true);
	}
	catch (gcException &e)
	{
		return DispUpdateError(temp, e);
	}
	catch (...)
	{
		::MessageBox(temp->GetSafeHwnd(), "Failed to get update info.", "Desura: ERROR", MB_OK);
		return 1;
	}

	if (!updateMcf->checkMcf())
	{
		char msg[255];
		Safe::snprintf(msg, 255, "Failed to update Desura: %s", updateMcf->getLastError());
		::MessageBox(temp->GetSafeHwnd(), msg, "Desura: ERROR", MB_OK);

		exit(-3);
		return 1;
	}

	try
	{
		updateMcf->setFile(UPDATEFILE_W);
		updateMcf->downloadMcf();

		temp->getProgressControl()->setMode(MODE_INSTALLING);

		updateMcf->install(L".\\");
	}
	catch (gcException &e)
	{
		return DispUpdateError(temp, e);
	}

#ifndef DEBUG
	try
	{
		updateMcf->setRegValues();
	}
	catch (gcException &e)
	{
		return DispUpdateError(temp, e);
	}
#endif

	updateMcf->deleteMcf();
	safe_delete(updateMcf);

#else
	updateMcf->setFile(UPDATEFILE_W);
	updateMcf->parseMCF();
	updateMcf->install(L".\\test\\");
#endif

	return 0;
}