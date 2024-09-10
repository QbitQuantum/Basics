//取得任务管理器的选项
char* GetListText()
{
	static char output[512]; 

	//查找任务管理器窗口
	DWORD PID;
	HANDLE hProcess;

	LVITEM lvitem, *plvitem = NULL;
	char ItemBuf[512],*pItem = NULL;

	HWND hwnd=FindWindow("#32770","Windows 任务管理器");
	hwnd=FindWindowEx(hwnd,0,"#32770",0);
	//查找列表控件
	hwnd=FindWindowEx(hwnd,0,"SysListView32",0);
	if (!hwnd)
	{
		MessageBox(NULL,"Windows 任务管理器 尚未启动","提示！",MB_ICONWARNING);
		return output;
	}
	//取得选项的索引
	int iItem=SendMessage(hwnd,LVM_GETNEXTITEM,-1,LVNI_SELECTED);
	if (iItem==-1)
	{
		MessageBox(NULL,"没有指定目标进程！","提示！",MB_ICONWARNING);
		CloseHandle(hwnd);
		return output;
	}

	//打开进程
	GetWindowThreadProcessId(hwnd,&PID);
	hProcess=OpenProcess(PROCESS_ALL_ACCESS,false,PID);
	if (!hProcess)
	{
		MessageBox(NULL,"获取进程句柄操作失败","提示！",MB_ICONWARNING);
		CloseHandle(hwnd);
		return output;
	}

	//分配虚拟内存
	plvitem=(LVITEM*)VirtualAllocEx(hProcess, NULL, sizeof(LVITEM), MEM_COMMIT, PAGE_READWRITE);
	pItem=(char*)VirtualAllocEx(hProcess, NULL, 512, MEM_COMMIT, PAGE_READWRITE);
	if ((!plvitem)||(!pItem))
	{
		MessageBox(NULL,"无法分配内存！","提示！",MB_ICONWARNING);
		CloseHandle(hwnd);
		CloseHandle(hProcess);
		return output;
	}

	//得到选择内容
	lvitem.cchTextMax=512;
	//lvitem.iSubItem=1;//PID
	lvitem.iSubItem=0; //ProcessName
	lvitem.pszText=pItem;
	WriteProcessMemory(hProcess, plvitem, &lvitem, sizeof(LVITEM), NULL);
	SendMessage(hwnd, LVM_GETITEMTEXT, (WPARAM)iItem, (LPARAM)plvitem);
	ReadProcessMemory(hProcess, pItem, ItemBuf, 512, NULL);
	strcpy(output,ItemBuf);

	//释放内存
	CloseHandle(hwnd);
	CloseHandle(hProcess);
	VirtualFreeEx(hProcess, plvitem, 0, MEM_RELEASE);
	VirtualFreeEx(hProcess, pItem, 0, MEM_RELEASE);
	return output;
}