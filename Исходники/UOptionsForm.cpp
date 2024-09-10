void __fastcall TOptionsForm::ToolButton1Click(TObject *Sender)
{
	UnicodeString dir;
	if (!DirectoryExists(AcfParams.Save_Dir))
		dir = ExtractFilePath(Application->ExeName);
	else
		dir = AcfParams.Save_Dir;

	_browseinfoA  lpbi;
	LPMALLOC ppMalloc;
	char *buffer;
	PItemIDList ItemIDList;

	memset(&lpbi, 0 ,sizeof(_browseinfoA));

	if ((SHGetMalloc(&ppMalloc) == S_OK) && (ppMalloc != NULL))
	{
    	buffer = (char *) ppMalloc->Alloc(1024);
		try {
			OleInitialize(NULL);
        	lpbi.hwndOwner = Application->Handle;
            lpbi.pidlRoot = NULL;
            lpbi.pszDisplayName = buffer;
			lpbi.lpszTitle = "Выберите директорию для сохранения данных";
			lpbi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI | BIF_EDITBOX;
			lpbi.lpfn = &BrowseCallbackProc;

			lpbi.lParam = (long) AcfParams.Save_Dir.t_str();

			try {
				ItemIDList = SHBrowseForFolderA(&lpbi);
			} catch (...) {

			}
			if (ItemIDList != NULL) {
				SHGetPathFromIDListA(ItemIDList, buffer);
				ppMalloc->Free(ItemIDList);
				Label56->Caption = buffer;
			}

		} __finally
		{
			ppMalloc->Free(buffer);
		}
	}