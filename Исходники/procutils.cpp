wxString ProcUtils::GetProcessNameByPid(long pid)
{
#ifdef __WXMSW__
	//go over the process modules and get the full path of
	//the executeable
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;

	//  Take a snapshot of all modules in the specified process.
	hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, (DWORD)pid );
	if ( hModuleSnap == INVALID_HANDLE_VALUE ) {
		return wxEmptyString;
	}

	//  Set the size of the structure before using it.
	me32.dwSize = sizeof( MODULEENTRY32 );

	//  Retrieve information about the first module,
	//  and exit if unsuccessful
	if (!Module32First( hModuleSnap, &me32 )) {
		CloseHandle( hModuleSnap );    // Must clean up the
		// snapshot object!
		return wxEmptyString;
	}

	//get the name of the process (it is located in the first entry)
	CloseHandle( hModuleSnap );
	return me32.szExePath;

#elif defined(__FreeBSD__)
	kvm_t *kvd;
	struct kinfo_proc *ki;
	int nof_procs;
	wxString cmd;

	if (!(kvd = kvm_openfiles(_PATH_DEVNULL, _PATH_DEVNULL, NULL, O_RDONLY, NULL)))
	    return wxEmptyString;

	if (!(ki = kvm_getprocs(kvd, KERN_PROC_PID, pid, &nof_procs))) {
	    kvm_close(kvd);
	    return wxEmptyString;
	}

	cmd = wxString(ki->ki_ocomm, wxConvUTF8);
	kvm_close(kvd);

	return (cmd);
#else
	wxArrayString output;
	ExecuteCommand(wxT("ps -A -o pid,command --no-heading"), output);
	//parse the output and search for our process ID
	for (size_t i=0; i< output.GetCount(); i++) {
		wxString line = output.Item(i);
		//remove whitespaces
		line = line.Trim();
		line = line.Trim(false);
		//get the process ID
		wxString spid = line.BeforeFirst(wxT(' '));
		long cpid(0);
		spid.ToLong( &cpid );
		if (cpid == pid) {
			//we got a match, extract the command, it is in the second column
			wxString command = line.AfterFirst(wxT(' '));
			return command;
		}
	}
	return wxEmptyString;	//Not implemented yet
#endif
}