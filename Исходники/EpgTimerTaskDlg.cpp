//CMD_TIMER_GUI_VIEW_EXECUTE Viewアプリ（EpgDataCap_Bon.exe）を起動
void CEpgTimerTaskDlg::CmdViewExecute(CMD_STREAM* pCmdParam, CMD_STREAM* pResParam)
{
	OutputDebugString(L"CEpgTimerTaskDlg::CmdViewExecute");
	wstring exeCmd = L"";

	ReadVALUE(&exeCmd, pCmdParam->data, pCmdParam->dataSize, NULL);

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si,sizeof(si));
	si.cb=sizeof(si);
	if( exeCmd.find(L".bat") != string::npos ){
		si.wShowWindow |= SW_SHOWMINNOACTIVE;
		si.dwFlags |= STARTF_USESHOWWINDOW;
	}

	BOOL bRet = CreateProcess( NULL, (WCHAR*)exeCmd.c_str(), NULL, NULL, FALSE, GetPriorityClass(GetCurrentProcess()), NULL, NULL, &si, &pi );
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	if( bRet == TRUE ){
		pResParam->dataSize = GetVALUESize(pi.dwProcessId);
		pResParam->data = new BYTE[pResParam->dataSize];
		WriteVALUE(pi.dwProcessId, pResParam->data, pResParam->dataSize, NULL);
		pResParam->param = CMD_SUCCESS;
	}else{
		pResParam->param = CMD_ERR;
	}
}