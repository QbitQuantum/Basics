int main (int argc, char* argv[]) {

	if (argc < 2) {
		printf("Usage:\n");
		printf("%s max_filename [manager [port]]\n",argv[0]);
		return 1;
	}

	//-- Come up with a temporary path for creating archives
	if (!ExpandEnvironmentStrings("%TEMP%",work_path,MAX_PATH)) {
		if (!ExpandEnvironmentStrings("%TMP%",work_path,MAX_PATH)) {
			if (!ExpandEnvironmentStrings("%HOMEPATH%",work_path,MAX_PATH))
				strcpy(work_path,"c:\\");
		}
	}

	if (work_path[strlen(work_path) - 1] != '\\')
		strcat(work_path,"\\");

	//-- Creates new manager access module instance
	MaxNetManager* manager = CreateManager();
	if (manager) {
		try {
			//-- Setup default manager port
			short port = DF_MGRPORT;
			//-- Placeholder for manager name
			char managername[MAX_PATH];
			//-- If we have a port defined, use it
			if (argc > 3)
				port = atoi(argv[3]);
			//-- If we have a host name (or ip address) for the manager, use it
			if (argc > 2)
				strcpy(managername,argv[2]);
			else {
				//-- Otherwise, find out who is the manager (if any)
				//   The API will broadcast a message looking for a
				//   manager using the given port. If a manager is
				//   found, its name/ip address will be placed in 
				//   "managername" below.
				if (!manager->FindManager(port,managername)) {
					printf("Could not find a Manager\n");
					DestroyManager(manager);
					return 1;
				}
			}
			//-- Connect to the manager
			manager->Connect(port,managername);
			//-- We're connected. Sumbmit Job(s)...
			WIN32_FIND_DATA find;
			HANDLE findhandle = FindFirstFile(argv[1],&find);
			if (findhandle != INVALID_HANDLE_VALUE) {
				char opath[MAX_PATH],npath[MAX_PATH];
				_splitpath(argv[1],opath,npath,0,0);
				strcat(opath,npath);
				if (opath[strlen(opath) - 1] != '\\')
					strcat(opath,"\\");
				do {
					strcpy(npath,opath);
					strcat(npath,find.cFileName);
					printf("Submitting %s...",find.cFileName);
					if (!assign_job(manager,npath))
						break;
					printf("\r%s Submitted successfully...\n",find.cFileName);
				} while (FindNextFile(findhandle,&find));
				FindClose(findhandle);
			}
			manager->Disconnect();
		//-- Exception Handler
		} catch (MaxNet* maxerr) {
			printf("\n%s (0x%08X)\n",maxerr->GetErrorText(),maxerr->GetError());
		}
		//-- Clean up manager instance
		DestroyManager(manager);
	}
	return 0;
}