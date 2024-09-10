/* ConnectToSkypeAPI
 * 
 * Purpose: Establish a connection to the Skype API
 * Params : ForceRestart - Kill Skype if it's running before restarting
 * Returns: 0 - Connecting succeeded
 *		   -1 - Something went wrong
 */
void ConnectToSkypeAPI(void *ForceRestart) {
	BOOL SkypeLaunched=FALSE;
	int counter=0, i, j;
	char *args[5];
	char *SkypeOptions[]={"/notray", "/nosplash", "/minimized"};
	char *szFuncName="ConnectToSkypeAPI";

	ResetEvent(SkypeReady);
	AttachStatus=-1;
	if ((BOOL)ForceRestart) {
		HANDLE hProc;
		DWORD dwPID=0;

		if (!hSkypeWnd) {
			OUTPUT("I can't kill Skype, as I don't even have its window handle!");
			return;
		}
		GetWindowThreadProcessId(hSkypeWnd, &dwPID);
		LOG(("%s: Shutting down Skype as it was not behaving the way it should...", szFuncName));
		if (hProc = OpenProcess(SYNCHRONIZE|PROCESS_TERMINATE, FALSE, dwPID)) {

			// Try to shutdown Skype the nice way by asking it to close
			EnumWindows((WNDENUMPROC)TerminateAppEnum, (LPARAM) dwPID);

			if(WaitForSingleObject(hProc, 10000)!=WAIT_OBJECT_0) {
				// Try it the hard way by killing it
				LOG(("%s: I tried it the nice way, but you were not listening! Now DIIIIEEE!", szFuncName));
				if (!TerminateProcess(hProc,0)) {
					OUTPUT("Argh, process refused to die, it's too mighty for me, I've given up");
					CloseHandle(hProc);
					return;
				}
				LOG(("%s: Process killed! >:)", szFuncName));
			}
			CloseHandle(hProc);
		}
	}
	do {
		/*	To initiate communication, Client should broadcast windows message
			('SkypeControlAPIDiscover') to all windows in the system, specifying its own
			window handle in wParam parameter.
		 */
		LOG(("%s: Sending discover message..", szFuncName));
		SendMessageTimeout(HWND_BROADCAST, ControlAPIDiscover, (WPARAM)hWnd, 0, SMTO_ABORTIFHUNG, 3000, NULL);
		LOG(("%s: Discover message sent, waiting for Skype to become ready..", szFuncName));

		/*	In response, Skype responds with
			message 'SkypeControlAPIAttach' to the handle specified, and indicates
			connection status
			SkypeReady is set if there is an answer by Skype other than API_AVAILABLE.
			If there is no answer after 3 seconds, launch Skype as it's propably
			not running.
		*/
		if (WaitForSingleObject(SkypeReady, 3000)==WAIT_TIMEOUT &&
			AttachStatus!=SKYPECONTROLAPI_ATTACH_PENDING_AUTHORIZATION) 
		{
			if (hWnd==NULL) {
				LOG(("%s: hWnd of SkypeDispatchWindow not yet set..", szFuncName));
				continue;
			}
			if (!SkypeLaunched && skype_path) {
				LOG(("%s: Starting Skype, as it's not running", szFuncName));
				args[0]=skype_path;
				j=1;
				for (i=0; i<3; i++) {
					args[j]=SkypeOptions[i];
					LOG(("%s: Using Skype parameter: ", szFuncName, args[j]));
					j++;
				}
				args[j]=NULL;
				_spawnv(_P_NOWAIT, skype_path, args);
				ResetEvent(SkypeReady);
				SkypeLaunched=TRUE;
				LOG(("%s: Skype process started.", szFuncName));
				// Skype launching iniciated, keep sending Discover messages until it responds.
				continue;
			} else {
				LOG(("%s: Check if Skype was launchable..", szFuncName));
				if (!skype_path) {
					OUTPUT("There was no correct path for Skype application");
					bail_out(1);
					return;
				}
				LOG("%s: Trying to attach: #%d", szFuncName, counter));
				counter++;
				if (counter==5) {
					OUTPUT("ERROR: Skype not running / too old / working!");
					bail_out(1);
					return;
				}
			}
		}
		LOG(("%s: Attachstatus %d", szFuncName, AttachStatus));
	} while (AttachStatus==SKYPECONTROLAPI_ATTACH_API_AVAILABLE || AttachStatus==-1);
	
	while (AttachStatus==SKYPECONTROLAPI_ATTACH_PENDING_AUTHORIZATION) Sleep(1000);
	LOG(("%s: Attachstatus %d", szFuncName, AttachStatus));
	if (AttachStatus!=SKYPECONTROLAPI_ATTACH_SUCCESS) {
		switch(AttachStatus) {
			case SKYPECONTROLAPI_ATTACH_REFUSED:
				OUTPUT("Skype refused the connection :(");
				break;
			case SKYPECONTROLAPI_ATTACH_NOT_AVAILABLE:
				OUTPUT("The Skype API is not available");
				break;
			default:
				LOG(("%s: ERROR: AttachStatus: %d", szFuncName, AttachStatus));
				OUTPUT("Wheee, Skype won't let me use the API. :(");
		}
		bail_out(1);
		return;
	}
	OUTPUT("Attached to Skype successfully.");
	if (!WatchDogRunning)
		if (_beginthread(WatchDogTimer, 0, NULL)==-1) {
			OUTPUT("Cannot start Watchdog.");
			bail_out(1);
		}
	return;
}