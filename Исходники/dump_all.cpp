INT_PTR CALLBACK DlgProc(HWND hdlg, UINT wmsg, WPARAM wparam, LPARAM lparam){
	HANDLE phandle;
	ULONG index;
	OPENFILENAME ofn;
	HICON icon;

	switch (wmsg){
		case WM_INITDIALOG:
			GlobalList = GetDlgItem(hdlg, IDC_LIST1);
			icon = ::LoadIconA(GetModuleHandleA(0), (LPSTR)IDI_ICON1);
			SendMessageA(hdlg, WM_SETICON, ICON_SMALL, (LPARAM)icon);
			SendMessageA(GlobalList, LB_RESETCONTENT, 0,0);
			::EnumProcesses(pids, 4096 * sizeof(DWORD), &needed);
			num_of_processes = needed / sizeof(DWORD);
			for (DWORD i = 0; i < num_of_processes; i++){
				phandle = ::OpenProcess(PROCESS_ALL_ACCESS, false, pids[i]);
				if (!phandle){
					wsprintf(buffer, "%.04X - process can't be opened", pids[i]);
					SendMessageA(GlobalList, LB_ADDSTRING, 0, (LPARAM)buffer);
					continue;
				}
				
				if (!EnumProcessModules(phandle, modules, 4096 * sizeof(HMODULE), &needed)){
					::CloseHandle(phandle);
					wsprintfA(buffer, "%.04X - can't obtain name", pids[i]);
					SendMessageA(GlobalList, LB_ADDSTRING, 0, (LPARAM)buffer);
					continue;
				}

				if (!::GetModuleFileNameExA(phandle, modules[0], proc_name, 4096)){
					::CloseHandle(phandle);
					wsprintfA(buffer, "%.04X - can't obtain name", pids[i]);
					SendMessageA(GlobalList, LB_ADDSTRING, 0, (LPARAM)buffer);
					continue;
				}

				wsprintfA(buffer, "%.04X - %s", pids[i], proc_name);
				SendMessageA(GlobalList, LB_ADDSTRING, 0, (LPARAM)buffer);
				::CloseHandle(phandle);
			}
			return 1;
		case WM_CLOSE:
			EndDialog(hdlg, 0);
			return 1;
		case WM_COMMAND:
			if (wparam == ID_DUMP){
				index = SendMessageA(GlobalList, LB_GETCURSEL, 0,0);
				if (index == LB_ERR){
					MessageBoxA(hdlg, "select process for dumping...", 0, 0);
					return 1;
				}
				mym(&ofn, 0, sizeof(OPENFILENAME));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.lpstrFilter = "Anyfile\0*.*\0\0";
				ofn.lpstrFile = (LPSTR)x_alloc(MAX_PATH);
				ofn.nMaxFile = MAX_PATH;
				ofn.hwndOwner = hdlg;
				if (!GetSaveFileNameA(&ofn)){
					MessageBoxA(hdlg, "select some file...", 0, 0);
					x_free(ofn.lpstrFile);
					return 1;
				}

				char *dir_name = ofn.lpstrFile + ::lstrlenA(ofn.lpstrFile) + 1;
				while (*dir_name != '\\')
					dir_name--;
				
				dir_name[0] = 0;
				dump_all(pids[index], ofn.lpstrFile);
				MessageBoxA(hdlg, "duming done...", "success", 0);
				x_free(ofn.lpstrFile);
				return 1;
			}
			
			if (wparam == ID_REFRESH){
				SendMessageA(GlobalList, LB_RESETCONTENT, 0,0);
				::EnumProcesses(pids, 4096 * sizeof(DWORD), &needed);
				num_of_processes = needed / sizeof(DWORD);
				for (DWORD i = 0; i < num_of_processes; i++){
					phandle = ::OpenProcess(PROCESS_ALL_ACCESS, false, pids[i]);
					if (!phandle){
						wsprintf(buffer, "%.04X - process can't be opened", pids[i]);
						SendMessageA(GlobalList, LB_ADDSTRING, 0, (LPARAM)buffer);
						continue;
					}
				
					if (!EnumProcessModules(phandle, modules, 4096 * sizeof(HMODULE), &needed)){
						::CloseHandle(phandle);
						wsprintfA(buffer, "%.04X - can't obtain name", pids[i]);
						SendMessageA(GlobalList, LB_ADDSTRING, 0, (LPARAM)buffer);
						continue;
					}

					if (!::GetModuleFileNameExA(phandle, modules[0], proc_name, 4096)){
						::CloseHandle(phandle);
						wsprintfA(buffer, "%.04X - can't obtain name", pids[i]);
						SendMessageA(GlobalList, LB_ADDSTRING, 0, (LPARAM)buffer);
						continue;
					}

					wsprintfA(buffer, "%.04X - %s", pids[i], proc_name);
					SendMessageA(GlobalList, LB_ADDSTRING, 0, (LPARAM)buffer);
					::CloseHandle(phandle);
				}
				return 1;
			}
		default:
			return 0;
	}

	return 0;
}