BOOL ReadFromFile()
{
	IFileOpenDialog *pDlg;
	COMDLG_FILTERSPEC FileTypes[] = {
		{ L"PS2 MemoryCard files", L"*.ps2" },
		{ L"All files", L"*.*" }
	};

	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDlg));
	WCHAR cPath[MAX_PATH] = L"";
	GetCurrentDirectoryW(sizeof(cPath) / sizeof(cPath[0]), cPath);
	IShellItem *psiFolder, *psiParent;
	SHCreateItemFromParsingName(cPath, NULL, IID_PPV_ARGS(&psiFolder));
	psiFolder->GetParent(&psiParent);

	//初期フォルダの指定
	pDlg->SetFolder(psiFolder);
	//フィルターの指定
	pDlg->SetFileTypes(_countof(FileTypes), FileTypes);
	//ダイアログ表示
	hr = pDlg->Show(NULL);

	//ファイル名
	LPOLESTR pwsz = NULL;
	if (SUCCEEDED(hr))
	{
		IShellItem *pItem;
		hr = pDlg->GetResult(&pItem);
		if (SUCCEEDED(hr))
		{

			hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pwsz);
			if (SUCCEEDED(hr))
			{
				HANDLE hFile;
				hFile = CreateFile(pwsz, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
				if (hFile)
				{
					DWORD BytesRead;
					BOOL b = ReadFile(hFile, &(byteMemDat.Byte), sizeof(byteMemDat), &BytesRead, NULL);
					if (BytesRead)
					{
						CloseHandle(hFile);
					}
				}
			}
		}
	}
	UpdateDataList(&byteMemDat);
	return TRUE;
}