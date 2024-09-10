void FileList::DeleteFiles(const char *applicationDirectory)
{
	char fullPath[512];
	unsigned i,j;

	for (i=0; i < fileList.Size(); i++)
	{
		// The filename should not have .. in the path - if it does ignore it
		for (j=1; j < strlen(fileList[i].filename); j++)
		{
			if (fileList[i].filename[j]=='.' && fileList[i].filename[j-1]=='.')
			{
#ifdef _DEBUG
				assert(0);
#endif
				// Just cancel the deletion entirely
				return;
			}
		}

		strcpy(fullPath, applicationDirectory);
		strcat(fullPath, fileList[i].filename);
        _unlink(fullPath);
	}
}