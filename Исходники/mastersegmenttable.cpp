MasterSegmentTable::MasterSegmentTable()
{
#ifdef _MSC_VER
	const char* envp = getenv("SystemRoot");
	string SystemRoot;
	if (envp && *envp)
		SystemRoot = envp;
	else
		SystemRoot = "C:\\WINDOWS";
	string tmpEnv = "TMP=" + SystemRoot + "\\Temp";
	_putenv(tmpEnv.c_str());
#endif

	int i;
	bool initializer = false;
	
	RWLockKeys[0] = fShmKeys.KEYRANGE_EXTENTMAP_BASE;
	RWLockKeys[1] = fShmKeys.KEYRANGE_EMFREELIST_BASE;
	RWLockKeys[2] = fShmKeys.KEYRANGE_VBBM_BASE;
	RWLockKeys[3] = fShmKeys.KEYRANGE_VSS_BASE;
	RWLockKeys[4] = fShmKeys.KEYRANGE_CL_BASE;
		
    try
    {
        // if initializer is returned false, then this is not the first time for this key.
        rwlock[0].reset(new RWLock(RWLockKeys[0], &initializer));
	}
	catch (exception &e) 
    {
		cerr << "ControllerSegmentTable: RWLock() threw: " << e.what() << endl;
		throw;
	}
	if (rwlock[0] == NULL) {
		cerr << "ControllerSegmentTable(): RWLock() failed..?" << endl;
		throw runtime_error("ControllerSegmentTable(): RWLock() failed..?");
	}
	
	for (i = 1; i < nTables; i++)
		rwlock[i].reset(new RWLock(RWLockKeys[i]));
	
	makeMSTSegment();
	if (initializer) {
		initMSTData();
		rwlock[0]->write_unlock();
	}
	else {
		rwlock[0]->read_lock_priority();     // this is to synch with the initializer
		rwlock[0]->read_unlock();
	}
}