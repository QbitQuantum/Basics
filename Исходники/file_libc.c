static err_t EnumDir(filestream* p,const tchar_t* Exts,bool_t ExtFilter,streamdir* Item)
{
	struct dirent *Dirent;

	if (!p->FindDir)
		return ERR_END_OF_FILE;

	Item->FileName[0] = 0;
    Item->Size = INVALID_FILEPOS_T;

	while (!Item->FileName[0] && (Dirent = readdir(p->FindDir)) != NULL)
	{
	    tchar_t FilePath[MAXPATH];
	    struct stat file_stats;
        
        if (Dirent->d_name[0]=='.') // skip hidden files and current directory
            continue;

	    tcscpy_s(FilePath, TSIZEOF(FilePath), p->DirPath);
	    tcscat_s(FilePath, TSIZEOF(FilePath), Dirent->d_name);
	    tcscpy_s(Item->FileName,TSIZEOF(Item->FileName), Dirent->d_name);

	    stat(FilePath, &file_stats);

	    Item->ModifiedDate = LinuxToDateTime(file_stats.st_mtime);
	    if (S_ISDIR(file_stats.st_mode))
        {
            Item->Type = FTYPE_DIR;
		    Item->Size = INVALID_FILEPOS_T;
        }
	    else
	    {
		    Item->Size = file_stats.st_size;
		    Item->Type = CheckExts(Item->FileName,Exts);

			if (!Item->Type && ExtFilter)
				Item->FileName[0] = 0; // skip
	    }
	}

	if (!Item->FileName[0])
	{
		closedir(p->FindDir);
		p->FindDir = NULL;
		return ERR_END_OF_FILE;
	}

	return ERR_NONE;
}