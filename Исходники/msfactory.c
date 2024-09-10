int ms_factory_load_plugins(MSFactory *factory, const char *dir){
	int num=0;
#if defined(_WIN32) && !defined(_WIN32_WCE)
	WIN32_FIND_DATA FileData;
	HANDLE hSearch;
	char szDirPath[1024];
#ifdef UNICODE
	wchar_t wszDirPath[1024];
#endif
	char szPluginFile[1024];
	BOOL fFinished = FALSE;
	const char *tmp = NULL;
	BOOL debug = FALSE;
#ifndef MS2_WINDOWS_UNIVERSAL
	tmp = getenv("DEBUG");
#endif
	debug = (tmp != NULL && atoi(tmp) == 1);

	snprintf(szDirPath, sizeof(szDirPath), "%s", dir);

	// Start searching for .dll files in the current directory.
#ifdef MS2_WINDOWS_DESKTOP
	snprintf(szDirPath, sizeof(szDirPath), "%s\\*.dll", dir);
#else
	snprintf(szDirPath, sizeof(szDirPath), "%s\\libms*.dll", dir);
#endif
#ifdef UNICODE
	mbstowcs(wszDirPath, szDirPath, sizeof(wszDirPath));
	hSearch = FindFirstFileExW(wszDirPath, FindExInfoStandard, &FileData, FindExSearchNameMatch, NULL, 0);
#else
	hSearch = FindFirstFileExA(szDirPath, FindExInfoStandard, &FileData, FindExSearchNameMatch, NULL, 0);
#endif
	if (hSearch == INVALID_HANDLE_VALUE)
	{
		ms_message("no plugin (*.dll) found in [%s] [%d].", szDirPath, (int)GetLastError());
		return 0;
	}
	snprintf(szDirPath, sizeof(szDirPath), "%s", dir);

	while (!fFinished)
	{
		/* load library */
#ifdef MS2_WINDOWS_DESKTOP
		UINT em=0;
#endif
		HINSTANCE os_handle;
#ifdef UNICODE
		wchar_t wszPluginFile[2048];
		char filename[512];
		wcstombs(filename, FileData.cFileName, sizeof(filename));
		snprintf(szPluginFile, sizeof(szPluginFile), "%s\\%s", szDirPath, filename);
		mbstowcs(wszPluginFile, szPluginFile, sizeof(wszPluginFile));
#else
		snprintf(szPluginFile, sizeof(szPluginFile), "%s\\%s", szDirPath, FileData.cFileName);
#endif
#ifdef MS2_WINDOWS_DESKTOP
		if (!debug) em = SetErrorMode (SEM_FAILCRITICALERRORS);

#ifdef UNICODE
		os_handle = LoadLibraryExW(wszPluginFile, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
#else
		os_handle = LoadLibraryExA(szPluginFile, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
#endif
		if (os_handle==NULL)
		{
			ms_message("Fail to load plugin %s with altered search path: error %i",szPluginFile,(int)GetLastError());
#ifdef UNICODE
			os_handle = LoadLibraryExW(wszPluginFile, NULL, 0);
#else
			os_handle = LoadLibraryExA(szPluginFile, NULL, 0);
#endif
		}
		if (!debug) SetErrorMode (em);
#else
		os_handle = LoadPackagedLibrary(wszPluginFile, 0);
#endif
		if (os_handle==NULL)
			ms_error("Fail to load plugin %s: error %i", szPluginFile, (int)GetLastError());
		else{
			init_func_t initroutine;
			char szPluginName[256];
			char szMethodName[256];
			char *minus;
#ifdef UNICODE
			snprintf(szPluginName, sizeof(szPluginName), "%s", filename);
#else
			snprintf(szPluginName, sizeof(szPluginName), "%s", FileData.cFileName);
#endif
			/*on mingw, dll names might be libsomething-3.dll. We must skip the -X.dll stuff*/
			minus=strchr(szPluginName,'-');
			if (minus) *minus='\0';
			else szPluginName[strlen(szPluginName)-4]='\0'; /*remove .dll*/
			snprintf(szMethodName, sizeof(szMethodName), "%s_init", szPluginName);
			initroutine = (init_func_t) GetProcAddress (os_handle, szMethodName);
				if (initroutine!=NULL){
					initroutine(factory);
					ms_message("Plugin loaded (%s)", szPluginFile);
					// Add this new loaded plugin to the list (useful for FreeLibrary at the end)
					factory->ms_plugins_loaded_list=ms_list_append(factory->ms_plugins_loaded_list,os_handle);
					num++;
				}else{
					ms_warning("Could not locate init routine of plugin %s. Should be %s",
					szPluginFile, szMethodName);
				}
		}
		if (!FindNextFile(hSearch, &FileData)) {
			if (GetLastError() == ERROR_NO_MORE_FILES){
				fFinished = TRUE;
			}
			else
			{
				ms_error("couldn't find next plugin dll.");
				fFinished = TRUE;
			}
		}
	}
	/* Close the search handle. */
	FindClose(hSearch);

#elif defined(HAVE_DLOPEN)
	char plugin_name[64];
	DIR *ds;
	MSList *loaded_plugins = NULL;
	struct dirent *de;
	char *ext;
	char *fullpath;
	ds=opendir(dir);
	if (ds==NULL){
		ms_message("Cannot open directory %s: %s",dir,strerror(errno));
		return -1;
	}
	while( (de=readdir(ds))!=NULL){
		if (
#ifndef __QNX__
			(de->d_type==DT_REG || de->d_type==DT_UNKNOWN || de->d_type==DT_LNK) &&
#endif
			(ext=strstr(de->d_name,PLUGINS_EXT))!=NULL) {
			void *handle;
			snprintf(plugin_name, MIN(sizeof(plugin_name), ext - de->d_name + 1), "%s", de->d_name);
			if (ms_list_find_custom(loaded_plugins, (MSCompareFunc)strcmp, plugin_name) != NULL) continue;
			loaded_plugins = ms_list_append(loaded_plugins, ms_strdup(plugin_name));
			fullpath=ms_strdup_printf("%s/%s",dir,de->d_name);
			ms_message("Loading plugin %s...",fullpath);

			if ( (handle=dlopen(fullpath,RTLD_NOW))==NULL){
				ms_warning("Fail to load plugin %s : %s",fullpath,dlerror());
			}else {
				char *initroutine_name=ms_malloc0(strlen(de->d_name)+10);
				char *p;
				void *initroutine=NULL;
				strcpy(initroutine_name,de->d_name);
				p=strstr(initroutine_name,PLUGINS_EXT);
				if (p!=NULL){
					strcpy(p,"_init");
					initroutine=dlsym(handle,initroutine_name);
				}

#ifdef __APPLE__
				if (initroutine==NULL){
					/* on macosx: library name are libxxxx.1.2.3.dylib */
					/* -> MUST remove the .1.2.3 */
					p=strstr(initroutine_name,".");
					if (p!=NULL)
					{
						strcpy(p,"_init");
						initroutine=dlsym(handle,initroutine_name);
					}
				}
#endif

				if (initroutine!=NULL){
					init_func_t func=(init_func_t)initroutine;
					func(factory);
					ms_message("Plugin loaded (%s)", fullpath);
					num++;
				}else{
					ms_warning("Could not locate init routine of plugin %s",de->d_name);
				}
				ms_free(initroutine_name);
			}
			ms_free(fullpath);
		}
	}
	ms_list_for_each(loaded_plugins, ms_free);
	ms_list_free(loaded_plugins);
	closedir(ds);
#else
	ms_warning("no loadable plugin support: plugins cannot be loaded.");
	num=-1;
#endif
	return num;
}