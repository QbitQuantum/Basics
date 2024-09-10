char *getSourceName(HWND hwnd)
{
HANDLE hProcess;
DWORD processid;
char filename[MAX_PATH], *pname;
SIZE_T bread;
//HWND hdlgPE;
	
	memset(filename, 0, MAX_PATH);
	GetWindowThreadProcessId(hwnd, &processid);
	hProcess = OpenProcess(PROCESS_VM_READ, FALSE, processid);
//	hdlgPE=SendMessage(hwnd,WM_WA_IPC,IPC_GETWND_PE,IPC_GETWND);
	pname=(char*)SendMessage(hwnd,WM_WA_IPC,SendMessage(hwnd,WM_WA_IPC,0,IPC_GETLISTPOS),IPC_GETPLAYLISTFILE);
	ReadProcessMemory(hProcess, pname, filename, MAX_PATH, &bread);
	CloseHandle(hProcess);
	return strdup(filename);
}