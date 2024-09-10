void 
CTextureAtlasCreatorContext::Save()
{
	CHAR8 strOpenName[512] = "";
	OPENFILENAMEA FileName;
	memset(&FileName, 0, sizeof(OPENFILENAMEA));
	FileName.lStructSize = sizeof(OPENFILENAMEA);
	FileName.hwndOwner = reinterpret_cast<HWND>(Ascension::Renderer().GetWindowHandle());
	FileName.hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(NULL));
	FileName.lpstrFilter = NULL;
	FileName.lpstrCustomFilter = NULL;
	FileName.nMaxCustFilter = NULL;
	FileName.lpstrFilter = "Ascension Atlas Files\0*.ascatl*\0\0";
	FileName.nFilterIndex = 1;
	FileName.lpstrFile = strOpenName;
	FileName.nMaxFile = 512;
	FileName.lpstrFileTitle = NULL;
	FileName.lpstrTitle = "Save File";
	FileName.Flags = OFN_EXPLORER;

	if(TRUE == GetSaveFileNameA(&FileName))
	{
		SaveAtlas(strOpenName);
	}
}