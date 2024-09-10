int
visit_path_recursively(const char* pcszPath, operate_callback file_func,
		       operate_callback dir_func,
		       operate_callback dir_func2){
#ifndef WIN32
	struct stat		statbuf;
	struct dirent		*dirp;
	DIR			*dp;
	char			szPath[MAX_PATH];
	int			nRet = 1;
	
	lstat(pcszPath, &statbuf);

	/* if it is a file, use file operation
	   callback function to process it */
	if (S_ISDIR(statbuf.st_mode) == 0){
		if ( file_func != NULL ){
			nRet = file_func( pcszPath );
			return nRet;
		}
		else
			return 1;
	}

	/* here it is qure a path, then try to open the directory */
	if ( (dp = opendir(pcszPath)) == NULL){
		write_log(LT_BOTH, "Error: Can't open directory: %s!\n",
			  szPath );
		return 0;
	}

	/* use directory operation callback function to process it */
	if ( dir_func != NULL ){
		nRet = dir_func(pcszPath);
		if ( nRet == 0 || nRet == 2 ){
			if ( nRet == 0 )
				write_log(LT_BOTH, "Error: when process %s using dir_func!\n", pcszPath);
			goto exit;
		}
	}

	/* Read the directory and visit its all child recursively */

	while ( (dirp = readdir(dp)) != NULL) {
		/* ignore dot and dot-dot */
		if (strcmp(dirp->d_name, ".") == 0  ||
		    strcmp(dirp->d_name, "..") == 0)
			continue;

		/* append name after slash */
		sprintf(szPath, "%s/%s", pcszPath, dirp->d_name);

		nRet = visit_path_recursively(szPath, file_func, dir_func, dir_func2);
		if ( nRet == 0 ){
			write_log(LT_BOTH, "Error: when process %s!\n", szPath);
			goto exit;
		}
		if ( dir_func2 != NULL ){
			nRet = dir_func2(szPath);
			if ( nRet == 0 ){
				write_log(LT_BOTH, "Error: when process %s using dir_func2!\n", szPath);				
				goto exit;
			}
		}
	}

 exit:
	/* close the directory which is opened before */
	if (closedir(dp) < 0)
		write_log(LT_BOTH, "Error: Can't close directory %s!\n", pcszPath);
	
	return nRet;
#else		//WIN32
	intptr_t		hFind;
	_finddata_t		FindData;
	char			szPath[MAX_PATH];
	int			nRet = 1;

    if ( SetCurrentDirectoryA(pcszPath) == 0 ){
		write_log(LT_BOTH, "Error: Can't set the current directory: %s!\n",
			  pcszPath);
		return 0;
	}

	hFind = _findfirst("*.*", &FindData);
	if (hFind == -1)
		return 0;

	do{
		if ( strcmp(FindData.name, ".") == 0 ||
		     strcmp(FindData.name, "..") == 0)
			continue;

		sprintf(szPath, "%s\\%s", pcszPath, FindData.name);
		if ( FindData.attrib & _A_SUBDIR ){
			if ( dir_func != NULL ){
				nRet = dir_func(szPath);
				if ( nRet == 0 )
					goto exit;
				else if ( nRet == 2 ){
					continue;
				}
			}

			nRet = visit_path_recursively(szPath, file_func, 
						      dir_func, dir_func2);
			if ( nRet == 0 )
				goto exit;
			
			if ( dir_func2 != NULL ){
				nRet = dir_func2(szPath);
				if ( nRet == 0 )
					goto exit;
			}
		}
		else{
            SetFileAttributesA(FindData.name, FILE_ATTRIBUTE_NORMAL);
			if ( file_func != NULL ){
				nRet = file_func( szPath );
				if ( nRet == 0 )
					goto exit;
			}
		}
	}while ( _findnext(hFind, &FindData) == 0 );

 exit:
	if ( _findclose(hFind) )
		write_log(LT_BOTH, "Error: Can't close directory %s!\n", 
			  pcszPath);
	
	return nRet;
#endif //WIN32
}