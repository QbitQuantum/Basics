BOOL CALLBACK EnumChildProcEx(HWND hwnd, LPARAM lParam)
{   
	CString strWindowName = GetContrlWindowTextEx(hwnd);
	if (strWindowName.Find("应用程序错误")>0)		//满足条件
	{
		//遍历其子窗口，如果找到确定按钮，发送双击消息
		WriteLog("找到错误框:"+strWindowName,0);
		try
		{
			CloseErrorWindowEx(hwnd);
		}
		catch (...)
		{
		}		
		return FALSE;
	}
	else
	{
		Delay(20,&g_iExitFlag);
		if (g_iExitFlag == TRUE)
		{
			return FALSE;
		}
		EnumChildWindows(hwnd,EnumChildProcEx,lParam);
	}
	return TRUE;   
}