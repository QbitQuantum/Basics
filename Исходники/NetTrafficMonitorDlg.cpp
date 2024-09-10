void CNetTrafficMonitorDlg::OnSelfStarting()
{
	TCHAR szFileFullPath[MAX_PATH] = { 0 };
	TCHAR szFileName[_MAX_FNAME] = { 0 };
	GetModuleFileName(NULL, szFileFullPath, MAX_PATH);							// 得到程序自身的全路径
	_wsplitpath(szFileFullPath, NULL, NULL, szFileName, NULL);					// 获得程序名
	HKEY hKey;
	LPCTSTR lpRun = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");	// 找到系统的启动项
	if (ERROR_SUCCESS == RegOpenKey(HKEY_CURRENT_USER, lpRun, &hKey))			// 打开启动项Key
	{
		if (m_bSelfStarting)
		{
			if (ERROR_SUCCESS == RegDeleteValue(hKey, szFileName))				// 删除一个子Key
			{
				m_bSelfStarting = FALSE;
			}
		}
		else
		{
			if (ERROR_SUCCESS == RegSetValueEx(hKey,
				szFileName,
				0,
				REG_SZ,
				(LPBYTE)szFileFullPath,
				(lstrlen(szFileFullPath) + 1) * sizeof(TCHAR)))					// 添加一个子Key,并设置值
			{
				m_bSelfStarting = TRUE;
			}
		}
	}
	RegCloseKey(hKey);															// 关闭注册表
}