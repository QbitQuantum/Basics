//
//	サービスとして起動したかチェック
//	実行ファイルのディレクトリと、カレントディレクトリを比較
//	out: TRUE .. サービスとして起動したと思われる
//
BOOL check_execute_service(void)
{
	TCHAR current_path[MAX_PATH];
	OSVERSIONINFO ovi;
	SC_HANDLE scm, sc;
	SERVICE_STATUS st;
	DWORD size;
	LPQUERY_SERVICE_CONFIG qsc;

	nt_flag = FALSE;
	service_install_flag = FALSE;
	service_stop_flag = FALSE;
	ovi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&ovi);
	if(ovi.dwPlatformId == VER_PLATFORM_WIN32_NT) {
		nt_flag = TRUE;
		GetCurrentDirectory(MAX_PATH, current_path);
		// 実行ファイルのパスとカレントパスが違う場合、
		// サービスとして起動されたと判定。
		// 起動ドライブのルートにこのプログラムが置かれてたり、
		// CreateProcess で違うディレクトリで起動されるとまずい
		// ような気がする。まあ大丈夫でしょう。いいかげん。
		if(_tcsicmp(execute_path, current_path)) {
			SetCurrentDirectory(execute_path);
			return TRUE;
		}
		// サービスインストールチェック
		if(scm = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE)) {
			if(sc = OpenService(scm, service_name, SERVICE_ALL_ACCESS)) {
				// サービスインストール済み
				service_install_flag = TRUE;
				// 2004/8/9
				QueryServiceConfig(sc, 0, 0, &size);
				qsc = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LPTR, size);
				QueryServiceConfig(sc, qsc, size, &size);
				if(qsc->dwStartType == SERVICE_AUTO_START) {
					auto_flag = 1;
				} else if(qsc->dwStartType == SERVICE_DEMAND_START) {
					auto_flag = 0;
				}
				if(qsc->dwServiceType & SERVICE_INTERACTIVE_PROCESS) {
					desktop_flag = 1;
				} else {
					desktop_flag = 0;
				}
				LocalFree(qsc);
				if(QueryServiceStatus(sc, &st)) {
					if(st.dwCurrentState != SERVICE_STOPPED) {
						service_stop_flag = TRUE;
					}
					ControlService(sc, SERVICE_CONTROL_STOP, &st);
					Sleep(500);
				} else {
					// サービスを停止できません。\nサービスの権限のあるユーザーでログインしてください。
					MessageBoxResourceText(NULL, IDS_ERROR_STOP_SERVICE, NULL, ERROR_HEADER, MB_OK);
				}
				CloseServiceHandle(sc);
			}
			CloseServiceHandle(scm);
		}
	}
	return FALSE;
}