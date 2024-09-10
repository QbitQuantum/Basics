static INT_PTR CALLBACK Window_StopwatchExportDlg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	(void)lParam; // unused
	switch(msg) {
	case WM_INITDIALOG:{
		wchar_t buf[128];
		api.GetStr(L"Timers", L"SwExT", buf, _countof(buf), L"");
		SetDlgItemText(hDlg,IDC_SWE_TOTAL,buf);
		api.GetStr(L"Timers", L"SwExL", buf, _countof(buf), L"");
		SetDlgItemText(hDlg, IDC_SWE_LAP, buf);
		SendMessage(hDlg, WM_COMMAND,IDOK, 0);
		Edit_SetSel(GetDlgItem(hDlg,IDC_SWE_OUT), 0, -1);
		SetFocus(GetDlgItem(hDlg,IDC_SWE_OUT));
		return FALSE;}
	case WM_DESTROY:{
		break;}
	case WM_COMMAND: {
			switch(LOWORD(wParam)) {
			case IDC_SWE_EXPORT:{
				wchar_t filename[MAX_PATH];
				unsigned buflen = (unsigned)SendDlgItemMessageA(hDlg,IDC_SWE_OUT,WM_GETTEXTLENGTH,0,0);
				char* buf = malloc(buflen + 1);
				if(buf && buflen){
					GetDlgItemTextA(hDlg, IDC_SWE_OUT, buf, buflen+1);
					*filename = '\0';
					if(SaveFileDialog(hDlg,filename,_countof(filename))){
						FILE* fp = _wfopen(filename, L"wb");
						if(fp){
							fwrite(buf, sizeof(buf[0]), buflen, fp);
							fclose(fp);
						}
					}
				}
				free(buf);
				break;}
			case IDOK:{
				wchar_t buf[128];
				GetDlgItemText(hDlg, IDC_SWE_TOTAL, buf, _countof(buf));
				if(!*buf){
					api.DelValue(L"Timers", L"SwExT");
					SetDlgItemText(hDlg, IDC_SWE_TOTAL, L"\\n--------------------\\n\\t");
				}else
					api.SetStr(L"Timers", L"SwExT", buf);
				GetDlgItemText(hDlg, IDC_SWE_LAP, buf, _countof(buf));
				if(!*buf){
					api.DelValue(L"Timers", L"SwExL");
					SetDlgItemText(hDlg, IDC_SWE_LAP, L"Lap \\#\\f: \\l (\\t)\\n");
				}else
					api.SetStr(L"Timers", L"SwExL", buf);
				export_text(hDlg);
				break;}
			case IDCANCEL:
				EndDialog(hDlg, TRUE);
			}
			return TRUE;
		}
	}
	return FALSE;
}