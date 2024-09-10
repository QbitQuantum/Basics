int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	if( lpCmdLine[0] == _T('-') || lpCmdLine[0] == _T('/') ){
		if( lstrcmpi(_T("install"), lpCmdLine + 1) == 0 ){
			bool installed = false;
			TCHAR exePath[512];
			if( GetModuleFileName(NULL, exePath, _countof(exePath)) != 0 ){
				SC_HANDLE hScm = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT | SC_MANAGER_CREATE_SERVICE);
				if( hScm != NULL ){
					SC_HANDLE hSrv = CreateService(
						hScm, SERVICE_NAME, SERVICE_NAME, 0, SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
						SERVICE_AUTO_START, SERVICE_ERROR_NORMAL, exePath, NULL, NULL, NULL, NULL, NULL);
					if( hSrv != NULL ){
						installed = true;
						CloseServiceHandle(hSrv);
					}
					CloseServiceHandle(hScm);
				}
			}
			if( installed == false ){
				//コンソールがないのでメッセージボックスで伝える
				MessageBox(NULL, L"Failed to install/remove " SERVICE_NAME L".\r\nRun as Administrator on Vista and later.", NULL, MB_ICONERROR);
			}
			return 0;
		}else if( lstrcmpi(_T("remove"), lpCmdLine + 1) == 0 ){
			bool removed = false;
			SC_HANDLE hScm = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
			if( hScm != NULL ){
				SC_HANDLE hSrv = OpenService(hScm, SERVICE_NAME, DELETE | SERVICE_STOP | SERVICE_QUERY_STATUS);
				if( hSrv != NULL ){
					SERVICE_STATUS srvStatus;
					if( QueryServiceStatus(hSrv, &srvStatus) != FALSE ){
						if( srvStatus.dwCurrentState == SERVICE_STOPPED || ControlService(hSrv, SERVICE_CONTROL_STOP, &srvStatus) != FALSE ){
							removed = DeleteService(hSrv) != FALSE;
						}
					}
					CloseServiceHandle(hSrv);
				}
				CloseServiceHandle(hScm);
			}
			if( removed == false ){
				MessageBox(NULL, L"Failed to install/remove " SERVICE_NAME L".\r\nRun as Administrator on Vista and later.", NULL, MB_ICONERROR);
			}
			return 0;
		}
	}


	if( IsInstallService(SERVICE_NAME) == FALSE ){
		//普通にexeとして起動を行う
		HANDLE hMutex = CreateMutex(NULL, TRUE, EPG_TIMER_BON_SRV_MUTEX);
		if( hMutex != NULL ){
			if( GetLastError() != ERROR_ALREADY_EXISTS ){
				StartDebugLog();
				//メインスレッドに対するCOMの初期化
				CoInitialize(NULL);
				CEpgTimerSrvMain* pMain = new CEpgTimerSrvMain;
				if( pMain->Main(false) == false ){
					OutputDebugString(_T("_tWinMain(): Failed to start\r\n"));
				}
				delete pMain;
				CoUninitialize();
				StopDebugLog();
			}
			ReleaseMutex(hMutex);
			CloseHandle(hMutex);
		}
	}else if( IsStopService(SERVICE_NAME) == FALSE ){
		//サービスとして実行
		HANDLE hMutex = CreateMutex(NULL, TRUE, EPG_TIMER_BON_SRV_MUTEX);
		if( hMutex != NULL ){
			if( GetLastError() != ERROR_ALREADY_EXISTS ){
				StartDebugLog();
				SERVICE_TABLE_ENTRY dispatchTable[] = {
					{ SERVICE_NAME, service_main },
					{ NULL, NULL }
				};
				if( StartServiceCtrlDispatcher(dispatchTable) == FALSE ){
					OutputDebugString(_T("_tWinMain(): StartServiceCtrlDispatcher failed\r\n"));
				}
				StopDebugLog();
			}
			ReleaseMutex(hMutex);
			CloseHandle(hMutex);
		}
	}else{
		//Stop状態なのでサービスの開始を要求
		bool started = false;
		SC_HANDLE hScm = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
		if( hScm != NULL ){
			SC_HANDLE hSrv = OpenService(hScm, SERVICE_NAME, SERVICE_START);
			if( hSrv != NULL ){
				started = StartService(hSrv, 0, NULL) != FALSE;
				CloseServiceHandle(hSrv);
			}
			CloseServiceHandle(hScm);
		}
		if( started == false ){
			OutputDebugString(_T("_tWinMain(): Failed to start\r\n"));
		}
	}

	return 0;
}