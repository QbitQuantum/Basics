clsMemDump::clsMemDump( HANDLE hProc, PTCHAR FileBaseName, DWORD64 BaseOffset, DWORD Size, QWidget *pParent)
{
	bool	isProtectionChanged = false;
	DWORD	OldProtection	= NULL,
			NewProtection	= PAGE_READWRITE,
			BytesWrote		= NULL;
	SIZE_T	BytesReaded		= NULL;
	LPVOID pBuffer			= malloc(Size);

	if(!ReadProcessMemory(hProc,(LPVOID)BaseOffset,pBuffer,Size,&BytesReaded))
	{
		if(!VirtualProtectEx(hProc,(LPVOID)BaseOffset,Size,NewProtection,&OldProtection))
		{
			QMessageBox::critical(pParent,"Nanomite","Failed to access Memory!",QMessageBox::Ok,QMessageBox::Ok);
			free(pBuffer);
			return;
		}
		isProtectionChanged = true;

		if(!ReadProcessMemory(hProc,(LPVOID)BaseOffset,pBuffer,Size,&BytesReaded))
		{
			QMessageBox::critical(pParent,"Nanomite","Failed to read Memory!",QMessageBox::Ok,QMessageBox::Ok);
			free(pBuffer);
			return;
		}
	}
	
	PTCHAR FileName = (PTCHAR)malloc(MAX_PATH * sizeof(TCHAR));
	if(wcslen(FileBaseName) <= 0)
		wsprintf(FileName,L"NANOMITEDUMP_%016I64X-%016I64X_%08X.bin",BaseOffset,BaseOffset + Size,Size);
	else
		wsprintf(FileName,L"%s_%016I64X-%016I64X_%08X.bin",FileBaseName,BaseOffset,BaseOffset + Size,Size);

	QString filePath = QFileDialog::getSaveFileName(pParent,
		"Please select a place to save the dump",
		QString("%1\\%2").arg(QDir::currentPath()).arg(QString::fromWCharArray(FileName)),
		"Dump files (*.dmp *.bin)",
		NULL,
		QFileDialog::DontUseNativeDialog);

	free(FileName);

	HANDLE hFile = CreateFile(filePath.toStdWString().c_str(), GENERIC_READ | GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		QMessageBox::critical(pParent,"Nanomite","Failed to create File!",QMessageBox::Ok,QMessageBox::Ok);
		free(pBuffer);
		return;
	}

	if(!WriteFile(hFile,pBuffer,Size,&BytesWrote,NULL))
		QMessageBox::critical(pParent,"Nanomite","Failed to write to File!",QMessageBox::Ok,QMessageBox::Ok);

	free(pBuffer);
	CloseHandle(hFile);

	if(isProtectionChanged && !VirtualProtectEx(hProc,(LPVOID)BaseOffset,Size,OldProtection,&NewProtection))
		QMessageBox::critical(pParent,"Nanomite","Failed to reprotect the Memory!",QMessageBox::Ok,QMessageBox::Ok);
	
	QMessageBox::information(pParent,"Nanomite","Memory Dump finished!",QMessageBox::Ok,QMessageBox::Ok);
}