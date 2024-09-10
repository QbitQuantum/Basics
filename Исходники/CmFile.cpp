string CmFile::BrowseFolder()   
{
	static char Buffer[MAX_PATH];
	BROWSEINFOA bi;//Initial bi 	
	bi.hwndOwner = NULL; 
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer; // Dialog can't be shown if it's NULL
	bi.lpszTitle = "BrowseFolder";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.iImage = NULL;


	LPITEMIDLIST pIDList = SHBrowseForFolderA(&bi); // Show dialog
	if(pIDList)	{	
		SHGetPathFromIDListA(pIDList, Buffer);
		if (Buffer[strlen(Buffer) - 1]  == '\\')
			Buffer[strlen(Buffer) - 1] = 0;

		return string(Buffer);
	}
	return string();   
}