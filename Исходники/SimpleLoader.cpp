int SimpleLoader::Load(const wchar_t *filename, ifc_playlistloadercallback *playlist)
{
	FILE *simpleFile = _wfopen(filename, L"rt");
	if (simpleFile)
	{
		wchar_t nextFile[1024];
		while (!feof(simpleFile))
		{
			if (fgetws(nextFile, 1024, simpleFile))
				playlist->OnFile(nextFile, 0, -1, 0);
		}
		return IFC_PLAYLISTLOADER_SUCCESS;
	}

	return IFC_PLAYLISTLOADER_FAILED;
	
}