int CLAMAPI Scan_Initialize(const wchar_t *pEnginesFolder, const wchar_t *pTempRoot, const wchar_t *pLicenseKey, BOOL bLoadMinDefs) {
    BOOL cant_convert;
    int ret;

    logg("*in Scan_Initialize(pEnginesFolder = %S, pTempRoot = %S)\n", pEnginesFolder, pTempRoot);
    if(!pEnginesFolder)
	FAIL(CL_ENULLARG, "pEnginesFolder is NULL");
    if(!pTempRoot)
	FAIL(CL_ENULLARG, "pTempRoot is NULL");
    if(lock_engine())
	FAIL(CL_ELOCK, "failed to lock engine");
    if(engine) {
	unlock_engine();
	FAIL(CL_ESTATE, "Already initialized");
    }

    if(!(engine = cl_engine_new())) {
	unlock_engine();
	FAIL(CL_EMEM, "Not enough memory for a new engine");
    }
    cl_engine_set_clcb_pre_cache(engine, filetype_cb);
    cl_engine_set_clcb_pre_scan(engine, prescan_cb);
    cl_engine_set_clcb_post_scan(engine, postscan_cb);
    
    minimal_definitions = bLoadMinDefs;
    if(bLoadMinDefs)
	logg("^MINIMAL DEFINITIONS MODE ON!\n");

    if(!WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, pTempRoot, -1, tmpdir, sizeof(tmpdir), NULL, &cant_convert) || cant_convert) {
	free_engine_and_unlock();
	FAIL(CL_EARG, "Can't translate pTempRoot");
    }
    ret = strlen(tmpdir);
    while(ret>0 && tmpdir[--ret] == '\\')
	tmpdir[ret] = '\0';
    if(!ret || ret + 8 + 1 >= sizeof(tmpdir)) {
	free_engine_and_unlock();
	FAIL(CL_EARG, "Bad or too long pTempRoot '%s'", tmpdir);
    }
    memcpy(&tmpdir[ret+1], "\\clamtmp", 9);
    cli_rmdirs(tmpdir);
    if((ret = SHCreateDirectoryExA(NULL, tmpdir, NULL) != ERROR_SUCCESS) && ret != ERROR_ALREADY_EXISTS) {
	free_engine_and_unlock();
	FAIL(CL_ETMPDIR, "Cannot create pTempRoot '%s': error %d", tmpdir, ret);
    }
    if((ret = cl_engine_set_str(engine, CL_ENGINE_TMPDIR, tmpdir))) {
	free_engine_and_unlock();
	FAIL(ret, "Failed to set engine tempdir to '%s': %s", tmpdir, cl_strerror(ret));
    }
    if(!WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, pEnginesFolder, -1, dbdir, sizeof(dbdir), NULL, &cant_convert) || cant_convert) {
	free_engine_and_unlock();
	FAIL(CL_EARG, "Can't translate pEnginesFolder");
    }
    ret = load_db();
    unlock_engine();

    if(!ret) {
	ResetEvent(monitor_event);
	if(!(monitor_hdl = CreateThread(NULL, 0, monitor_thread, NULL, 0, NULL)))
	    logg("^Failed to start db monitoring thread\n");
    }

    logg("*Scan_Initialize: returning %d\n", ret);
    return ret;
}