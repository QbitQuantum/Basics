VOID SvcInit(DWORD dwArgc, LPTSTR *lpszArgv)
{
	ghSvcStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (ghSvcStopEvent == NULL) {
        ReportSvcStatus(SERVICE_STOPPED, NO_ERROR, 0);
        return;
    }

    ReportSvcStatus(SERVICE_RUNNING, NO_ERROR, 0);

	HANDLE hMutex = NULL;

	LaunchGreenShieldConfig launchGreenShieldCfg;
	if(launchGreenShieldCfg.UpdateConfig()) {
		if(launchGreenShieldCfg.Valid()) {
		TSINFO4CXX("Load Config IsNoRemind: "
			<< launchGreenShieldCfg.IsNoRemind()
			<< ", noremindspanday: " 
			<< launchGreenShieldCfg.GetNoRemindSpanDay()
			<< ", intervaltime: "
			<< launchGreenShieldCfg.GetLaunchInterval()
			<< ", maxcntperday: "
			<< launchGreenShieldCfg.GetMaxCntPerDay()
			<< ", lastpull: "
			<< launchGreenShieldCfg.GetLastPull()
			<< ", cnt: "
			<< launchGreenShieldCfg.GetCnt());
		}
	}
	else {
		TSERROR4CXX(L"Load Config failed");
	}

	bool isVistaOrLatter = IsVistaOrLatter();

    while(1) {
        DWORD dwTimeToWait = 1000;
		if(hMutex == NULL) {
			if(::IsVistaOrLatter()) {
				SECURITY_ATTRIBUTES sa;
				char sd[SECURITY_DESCRIPTOR_MIN_LENGTH];
				sa.nLength = sizeof(sa);
				sa.bInheritHandle = FALSE;
				sa.lpSecurityDescriptor = &sd;
				if(::InitializeSecurityDescriptor(sa.lpSecurityDescriptor, SECURITY_DESCRIPTOR_REVISION)) {
					if(::SetSecurityDescriptorDacl(sa.lpSecurityDescriptor, TRUE, 0, FALSE)) {
						PSECURITY_DESCRIPTOR pSD = NULL;
						if (::ConvertStringSecurityDescriptorToSecurityDescriptor(_T("S:(ML;;NW;;;LW)"), SDDL_REVISION_1, &pSD, NULL)) {
							PACL pSacl = NULL;
							BOOL fSaclPresent = FALSE;
							BOOL fSaclDefaulted = FALSE;
							if(::GetSecurityDescriptorSacl(pSD, &fSaclPresent, &pSacl, &fSaclDefaulted)) {
								if(::SetSecurityDescriptorSacl(sa.lpSecurityDescriptor, TRUE, pSacl, FALSE)) {
									hMutex = ::CreateMutex(&sa, TRUE, L"Global\\{88813F63-0986-40f9-B224-DBCDDC75E731}-cleanaddin");
									if(hMutex != NULL && ::GetLastError() == ERROR_ALREADY_EXISTS) {
										::CloseHandle(hMutex);
										hMutex = NULL;
									}
								}
								// ::LocalFree(pSacl);
							}
							::LocalFree(pSD);
						}
					}
				}
			}
			else {
				hMutex = ::CreateMutex(NULL, TRUE, L"Global\\{88813F63-0986-40f9-B224-DBCDDC75E731}-cleanaddin");
				if(hMutex != NULL && ::GetLastError() == ERROR_ALREADY_EXISTS) {
					::CloseHandle(hMutex);
					hMutex = NULL;
				}
			}
		}

		// 判断是否更新配置 每小时更新一次配置
		__time64_t nCurrentTime = 0;
		_time64(&nCurrentTime);
		const tm* currentTime = _gmtime64(&nCurrentTime);
		int curYear = currentTime->tm_year + 1900;
		int curMonth = currentTime->tm_mon + 1;
		int curDay = currentTime->tm_mday;
		int curHour = currentTime->tm_hour;
		
		__time64_t nlastUpdateTime = launchGreenShieldCfg.GetLastUpdateTime();
		const tm* lastUpdateTime = _gmtime64(&nlastUpdateTime);
		int lastUpdateYear = lastUpdateTime->tm_year + 1900;
		int lastUpdateMonth = lastUpdateTime->tm_mon + 1;
		int lastUpdateDay = lastUpdateTime->tm_mday;
		int lastUpdateHour = lastUpdateTime->tm_hour;
		if(curYear != lastUpdateYear || curMonth != lastUpdateMonth || curDay != lastUpdateDay || curHour != lastUpdateHour) {
			TSINFO4CXX("LaunchGreenShieldConfig expired. Try update");
			if(launchGreenShieldCfg.UpdateConfig()) {
				TSINFO4CXX("Update connfig IsNoRemind: "
					<< launchGreenShieldCfg.IsNoRemind()
					<< ", noremindspanday: " 
					<< launchGreenShieldCfg.GetNoRemindSpanDay()
					<< ", intervaltime: "
					<< launchGreenShieldCfg.GetLaunchInterval()
					<< ", maxcntperday: "
					<< launchGreenShieldCfg.GetMaxCntPerDay()
					<< ", lastpull: "
					<< launchGreenShieldCfg.GetLastPull()
					<< ", cnt: "
					<< launchGreenShieldCfg.GetCnt());
			}
			else {
				TSERROR4CXX(L"Update config failed");
			}
		}

		if(hMutex == NULL || ProcessDetect::IsGreenShieldOrGreenShieldSetupRunning()) {
			dwTimeToWait = 1000;
		}
		else if(launchGreenShieldCfg.Valid() && launchGreenShieldCfg.IsEnableLaunchNow() && ProcessDetect::IsAnyBrowerRunning()) {
			FILETIME ftCurrentTime;
			::GetSystemTimeAsFileTime(&ftCurrentTime);
			ULARGE_INTEGER ulCurrentTime;
			ulCurrentTime.HighPart = ftCurrentTime.dwHighDateTime;
			ulCurrentTime.LowPart = ftCurrentTime.dwLowDateTime;
			unsigned long long ullCurrentTime = ulCurrentTime.QuadPart;
			do {
				HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
				if(hProcessSnap == INVALID_HANDLE_VALUE) {
					break;
				}
				::ScopeResourceHandle<HANDLE, BOOL (WINAPI*)(HANDLE)> autoCloseProcessSnap(hProcessSnap, ::CloseHandle);

				PROCESSENTRY32 pe32;
				pe32.dwSize = sizeof(PROCESSENTRY32);

				if(!Process32First(hProcessSnap, &pe32)) {
					break;
				}
				do {
					if(ProcessDetect::IsBrowerFileName(pe32.szExeFile)) {
						if(pe32.th32ProcessID == 0 || pe32.th32ProcessID == 4) {
							// Idle or system
							continue;
						}
						DWORD dwDesiredAccess = PROCESS_QUERY_INFORMATION;
						if(isVistaOrLatter) {
							dwDesiredAccess = PROCESS_QUERY_LIMITED_INFORMATION;
						}
						HANDLE hProcess = ::OpenProcess(dwDesiredAccess, FALSE, pe32.th32ProcessID);

						if (hProcess == NULL) {
							continue;
						}
						ScopeResourceHandle<HANDLE, BOOL (WINAPI*)(HANDLE)> autoCloseProcessHandle(hProcess, ::CloseHandle);
						FILETIME ftCreationTime;
						FILETIME ftExitTime;
						FILETIME ftKernelTime;
						FILETIME ftUserTime;
						if (!::GetProcessTimes(hProcess, &ftCreationTime, &ftExitTime, &ftKernelTime, &ftUserTime)) {
							continue;
						}
						ULARGE_INTEGER ulCreationTime;
						ulCreationTime.HighPart = ftCreationTime.dwHighDateTime;
						ulCreationTime.LowPart = ftCreationTime.dwLowDateTime;
						unsigned long long ullCreationTime = ulCreationTime.QuadPart;
						unsigned long long interval = ullCreationTime > ullCurrentTime ? ullCreationTime - ullCurrentTime : ullCurrentTime - ullCreationTime;
						if(interval > 5ull * 10ull * 1000ull * 1000ull) {
							continue;
						}

						if(launchGreenShieldCfg.CheckEnableLaunchNow()) {
							if(!::LaunchGreenShield(pe32.th32ProcessID)) {
								dwTimeToWait = 5 * 60 * 1000;
							}
						}
						break;
					}
				} while(Process32Next(hProcessSnap, &pe32));
			} while(false);
		}

		DWORD waitRet = ::WaitForSingleObject(ghSvcStopEvent, dwTimeToWait);
		if(waitRet == WAIT_FAILED) {
			break;
		}
		else if(waitRet == WAIT_OBJECT_0) {
			break;
		}
    }
	::CloseHandle(hMutex);
	ReportSvcStatus(SERVICE_STOPPED, NO_ERROR, 0);
}