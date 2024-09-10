tsk_plugin_t* tsk_plugin_create(const char* path)
{
	tsk_plugin_t* plugin;
	symbol_get_def_count funcptr_get_def_count;
	tsk_plugin_handle_t* handle;

#if TSK_UNDER_WINDOWS
#	if TSK_UNDER_WINDOWS_RT
	wchar_t* szPath = (wchar_t*)tsk_calloc(tsk_strlen(path) + 1, sizeof(wchar_t));
	static const wchar_t* szFormat = L"%hs";
	swprintf(szPath, tsk_strlen(path) * sizeof(wchar_t), szFormat, path);
	handle = LoadPackagedLibrary(szPath, 0x00000000);
	TSK_FREE(szPath);
#	else /* Windows desktop */
	UINT currErrMode = SetErrorMode(SEM_FAILCRITICALERRORS); // save current ErrorMode. GetErrorMode() not supported on XP.
	SetErrorMode(currErrMode | SEM_FAILCRITICALERRORS);
	handle = LoadLibraryA(path);
	SetErrorMode(currErrMode); // restore ErrorMode
#	endif
#else
	handle = dlopen(path, RTLD_NOW);
#endif

	if(!handle){
		TSK_DEBUG_ERROR("Failed to load library with path=%s", path);
		return tsk_null;
	}

	if(!(funcptr_get_def_count = (symbol_get_def_count)_tsk_plugin_handle_get_symbol(handle, TSK_PLUGIN_FUNC_NAME_DEF_COUNT))){
		TSK_DEBUG_ERROR("Cannot find function with name=%s", TSK_PLUGIN_FUNC_NAME_DEF_COUNT);
		_tsk_plugin_handle_destroy(&handle);
		return tsk_null;
	}

	if(!(plugin = (tsk_plugin_t*)tsk_object_new(&tsk_plugin_def_s))){
		TSK_DEBUG_ERROR("Failed to create plugin object");
		_tsk_plugin_handle_destroy(&handle);
		return tsk_null;
	}

	plugin->handle = handle;
	plugin->def_count = funcptr_get_def_count();
	plugin->path = tsk_strdup(path);

	TSK_DEBUG_INFO("Plugin with path=[%s] created with [%d] defs", plugin->path, plugin->def_count);

	return plugin;
}