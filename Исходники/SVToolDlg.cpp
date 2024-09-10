BOOL CSVToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_SHOW);
	m_Font.CreatePointFont(100, _T("微软雅黑"), NULL);
	m_static.SetFont(&m_Font, true);

	// TODO: 在此添加额外的初始化代码
	SetWindowText(_T("SVTool - V1.0"));
	
	CRect tabRect;

	m_tab.InsertItem(0,_T("ACPI"));
	m_tab.InsertItem(1,_T("CCTool"));

	CCTool.Create(IDD_DIALOG_CCTool, &m_tab);
	ACPI.Create(IDD_DIALOG_ACPI, &m_tab);

	m_tab.GetClientRect(&tabRect);
	tabRect.left += 5;                  
    tabRect.right -= 5;   
    tabRect.top += 25;   
    tabRect.bottom -= 5;

	//设置子对话框尺寸并移动到指定位置

	ACPI.MoveWindow(&tabRect);
	CCTool.MoveWindow(&tabRect);

	//分别设置隐藏和显示
	ACPI.ShowWindow(true);
	CCTool.ShowWindow(false);

	m_tab.SetCurSel(0);

	// 根据调整好的tabRect放置m_jzmDlg子对话框，并设置为显示   
    // CCTool.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
    // 根据调整好的tabRect放置m_androidDlg子对话框，并设置为隐藏   
    //ACPI.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW); 

	//ACPI
	TCHAR rbPath[MAX_PATH];
	GetModuleFileName(NULL,rbPath,MAX_PATH);
	ACPI.rootpath = rbPath;

	CString temp1;
	TCHAR TMP1[1024];
	DWORD dd;
	CRegKey KKey;
	CString HWinfo = ACPI.hardwareinfo();
	ACPI.SetDlgItemText(IDC_HWINFO,HWinfo);
	if(KKey.Open(HKEY_CURRENT_USER,_T("Software\\SVACPI\\ACPI Information")) == ERROR_SUCCESS)
	{
		AfxMessageBox(_T("1"));
		KKey.QueryStringValue(_T("OrigHWInfo"),TMP1,&dd);
		temp1 = TMP1;
		KKey.QueryStringValue(_T("ErrorPath"),TMP1,&dd);
		ACPI.errorpath = TMP1;
		if(ACPI.CheckDiffInfo(ACPI.ACPIs, temp1, HWinfo))
			ACPI.GetDlgItem(IDC_STATIC_Error)->EnableWindow(TRUE); 
	}
	KKey.Close();

	CRegKey hKey;
	if(hKey.Open(HKEY_CURRENT_USER,_T("Software\\SVACPI\\ACPI Information")) == ERROR_SUCCESS)
	{
		AfxMessageBox(_T("2"));
		TCHAR TMP[1024];
		CString temp;
		DWORD dwcount = 1024, dwType = REG_SZ;
		//从注册表中恢复设置
		hKey.QueryStringValue(_T("SetLoop"), TMP, &dwcount);
		temp = TMP;
		ACPI.SetDlgItemText(IDC_Loop, temp);

		hKey.QueryStringValue(_T("SetTime"), TMP, &dwcount);
		temp = TMP;
		ACPI.SetDlgItemText(IDC_Countdown, temp);
		ACPI.SetDlgItemText(IDC_time_to_run, temp);

		CRegKey lKey;
		if (lKey.Open(HKEY_CURRENT_USER, _T("Software\\SVACPI\\ACPI Information")) == ERROR_SUCCESS)
		{
			AfxMessageBox(_T("3"));
			lKey.QueryStringValue(_T("CurrState"), TMP, &dwcount);
			ACPI.ACPIs = TMP;
			temp = TMP;

			ULONGLONG a;
			lKey.QueryQWORDValue(_T("LastLoop"), a);
			CString Loop;
			Loop.Format(_T("%d"), a);
			ACPI.SetDlgItemText(IDC_Loop_time, Loop);
		}

		CString time;
		HKEY tKey;
		if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\SVACPI\\ACPI Information"), 0, KEY_READ | KEY_WRITE, &tKey) == ERROR_SUCCESS)
		{
			DWORD dwReturn = 1024;
			RegQueryValueEx(tKey, _T("RealTime"), NULL, &dwType, (LPBYTE)(&TMP), &dwReturn);
			time = TMP;
		}

		//S5开机初始化
		if(temp == _T("S5"))
		{
			ACPI.SetDlgItemText(IDC_S5BUTTON,_T("Stop S5"));
			ACPI.GetDlgItem(IDC_S4BUTTON)->EnableWindow(FALSE);
			ACPI.GetDlgItem(IDC_S3BUTTON)->EnableWindow(FALSE);
			ACPI.GetDlgItem(IDC_RbBUTTON)->EnableWindow(FALSE);
			ACPI.GetDlgItem(IDC_PBUTTON)->EnableWindow(TRUE);

			FILETIME ft; LARGE_INTEGER tmp; LONGLONG tmptime;
			SYSTEMTIME st;
			GetLocalTime(&st);

			SystemTimeToFileTime(&st, &ft);
			tmp.LowPart = ft.dwLowDateTime;
			tmp.HighPart = ft.dwHighDateTime;
			tmptime = tmp.QuadPart;

			tmptime += _ttoi64(time);
			tmp.QuadPart = tmptime;
			ft.dwLowDateTime = tmp.LowPart;
			ft.dwHighDateTime = tmp.HighPart;
			FileTimeToSystemTime(&ft, &st);
			SetLocalTime(&st);
		}
		//Reboot开机初始化
		else
		{
			ACPI.SetDlgItemText(IDC_RbBUTTON,_T("Stop Reboot"));
			ACPI.GetDlgItem(IDC_S4BUTTON)->EnableWindow(FALSE);
			ACPI.GetDlgItem(IDC_S3BUTTON)->EnableWindow(FALSE);
			ACPI.GetDlgItem(IDC_S5BUTTON)->EnableWindow(FALSE);
			ACPI.GetDlgItem(IDC_PBUTTON)->EnableWindow(TRUE);
		}
		hKey.Close();
		lKey.Close();
		ACPI.SetTimer(21,1000,NULL);
	}
	else
	{
		ACPI.SetDlgItemText(IDC_Loop,_T("9999"));
		ACPI.SetDlgItemText(IDC_Countdown,_T("15"));
		ACPI.SetDlgItemText(IDC_Loop_time,_T("0"));
		ACPI.SetDlgItemText(IDC_time_to_run,_T("-"));

		ACPI.SetDlgItemText(IDC_PBUTTON,_T("Pause"));
		ACPI.SetDlgItemText(IDC_S3BUTTON,_T("Run S1/S3"));
		ACPI.SetDlgItemText(IDC_S4BUTTON,_T("Run S4"));
		ACPI.SetDlgItemText(IDC_S5BUTTON,_T("Run S5"));
		ACPI.SetDlgItemText(IDC_RbBUTTON, _T("Reboot"));


		ACPI.GetDlgItem(IDC_PBUTTON)->EnableWindow(FALSE);
		ACPI.GetDlgItem(IDC_S3BUTTON)->EnableWindow(TRUE);
		ACPI.GetDlgItem(IDC_S4BUTTON)->EnableWindow(TRUE);
		ACPI.GetDlgItem(IDC_S5BUTTON)->EnableWindow(TRUE);
		ACPI.GetDlgItem(IDC_RbBUTTON)->EnableWindow(TRUE);
	}

	//copycompare
	CCTool.CheckDlgButton(IDC_200MS_RADIO, 1);
	CCTool.sourcepath = _T("D:\\CCData\\200MS");
	CCTool.SetDlgItemText(IDC_SOURCE_PATH_EDIT,CCTool.sourcepath);


	CString filename ;
	TCHAR SysTmpPath[MAX_PATH];
	GetTempPath(MAX_PATH,SysTmpPath);
	filename = SysTmpPath;
	filename+=_T("CCtool.bat");

	CFileFind finder;
	BOOL iffind = finder.FindFile(filename);
	if(iffind)
	{
		CFile CCbat;
		CCbat.Remove(filename);
	}
	
	CFile CCbat(filename, CFile::modeCreate|CFile::modeWrite);
	CCbat.Write("@echo off\r\necho CCLoop will start running in 10 seconds...\r\n", sizeof("@echo off\r\necho CCLoop will start running in 10 seconds...\r\n")-1);
	CCbat.Write("ping 127.0.0.1 -n 11>nul\r\n",sizeof("ping 127.0.0.1 -n 11>nul\r\n")-1);
	CCbat.Write("\r\n",sizeof("\r\n")-1);
	CCbat.Write("set /a looptime=0\r\n",sizeof("set /a looptime=0\r\n")-1);
	CCbat.Write("set sdisk=%2\r\n",sizeof("set sdisk=%2\r\n")-1);
	CCbat.Write("set ddisk=%3\r\n",sizeof("set ddisk=%3\r\n")-1);
	CCbat.Write("set s=%sdisk:~0,1%\r\n",sizeof("set s=%sdisk:~0,1%\r\n")-1);
	CCbat.Write("set d=%ddisk:~0,1%\r\n",sizeof("set d=%ddisk:~0,1%\r\n")-1);
	CCbat.Write("if not exist %d%:\\ color fc&echo ERROR!!! %d%:\\ is not EXIST!!!&pause\r\n",sizeof("if not exist %d%:\\ color fc&echo ERROR!!! %d%:\\ is not EXIST!!!&pause\r\n")-1);
	CCbat.Write("\r\n",sizeof("\r\n")-1);
	CCbat.Write("path=c:\\;c:\\windows\\command;c:\\windows\\system32;c:\\windows;C:\\WinNT\\system32;c:\\WinNT;c:\\windows\\sysWOW64;\r\n",sizeof("path=c:\\;c:\\windows\\command;c:\\windows\\system32;c:\\windows;C:\\WinNT\\system32;c:\\WinNT;c:\\windows\\sysWOW64;\r\n")-1);
	CCbat.Write("break=on\r\n",sizeof("break=on\r\n")-1);
	CCbat.Write("\r\n",sizeof("\r\n")-1);
	CCbat.Write("if exist c:\\%s%-%d%-%1.txt del /q c:\\%s%-%d%-%1.txt\r\n",sizeof("if exist c:\\%s%-%d%-%1.txt del /q c:\\%s%-%d%-%1.txt\r\n")-1);
	CCbat.Write("\r\n",sizeof("\r\n")-1);
	CCbat.Write(":start\r\n",sizeof(":start\r\n")-1);
	CCbat.Write("echo ************** (%s%) copy to (%d%) is starting ******************* >>C:\\%s%-%d%-%1.txt\r\n",sizeof("echo ************** (%s%) copy to (%d%) is starting ******************* >>C:\\%s%-%d%-%1.txt\r\n")-1);
	CCbat.Write("\r\n",sizeof("\r\n")-1);
	CCbat.Write(":l\r\n",sizeof(":l\r\n")-1);
	CCbat.Write("if exist %3 rd /s /q %3\r\n",sizeof("if exist %3 rd /s /q %3\r\n")-1);
	CCbat.Write("if exist D:\\%d%-%1-C rd /s /q D:\\%d%-%1-C\r\n",sizeof("if exist D:\\%d%-%1-C rd /s /q D:\\%d%-%1-C\r\n")-1);
	CCbat.Write("\r\n",sizeof("\r\n")-1);
	CCbat.Write(":loop\r\n",sizeof(":loop\r\n")-1);
	CCbat.Write("echo ************************************************************** >>C:\\%s%-%d%-%1.txt\r\n",sizeof("echo ************************************************************** >>C:\\%s%-%d%-%1.txt\r\n")-1);
	CCbat.Write("echo **************  Loop %looptime% is starting ****************** >>C:\\%s%-%d%-%1.txt\r\n",sizeof("echo **************  Loop %looptime% is starting ****************** >>C:\\%s%-%d%-%1.txt\r\n")-1);
	CCbat.Write("\r\n",sizeof("\r\n")-1);
	CCbat.Write("md %3\r\n",sizeof("md %3\r\n")-1);
	CCbat.Write("echo %time%\r\n",sizeof("echo %time%\r\n")-1);
	CCbat.Write("\r\n",sizeof("\r\n")-1);
	CCbat.Write("set copybgntime=%time%\r\n",sizeof("set copybgntime=%time%\r\n")-1);
	CCbat.Write("set copybgndate=%date%\r\n",sizeof("set copybgndate=%date%\r\n")-1);
	CCbat.Write("copy /Y %2 %3\r\n",sizeof("copy /Y %2 %3\r\n")-1);
	CCbat.Write("set copyendtime=%time%\r\n",sizeof("set copyendtime=%time%\r\n")-1);
	CCbat.Write("set copyenddate=%date%\r\n",sizeof("set copyenddate=%date%\r\n")-1);
	CCbat.Write("if errorlevel 1 color fc&echo ERROR happened when copy from %2 to %3 !!(no files were found) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n",sizeof("if errorlevel 1 color fc&echo ERROR happened when copy from %2 to %3 !!(no files were found) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n")-1);
	CCbat.Write("if errorlevel 4 color cf&echo ERROR happened when copy from %2 to %3 !!(there is not enough memory) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n",sizeof("if errorlevel 4 color cf&echo ERROR happened when copy from %2 to %3 !!(there is not enough memory) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n")-1);
	CCbat.Write("\r\n",sizeof("\r\n")-1);
	CCbat.Write("echo n|comp %2 %3\r\n",sizeof("echo n|comp %2 %3\r\n")-1);
	CCbat.Write("set compendtime=%time%\r\n",sizeof("set compendtime=%time%\r\n")-1);
	CCbat.Write("set compenddate=%date%\r\n",sizeof("set compenddate=%date%\r\n")-1);
	CCbat.Write("if errorlevel 1 color cf&echo ERROR happened when compare %2 with %3 !!(files are different) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n",sizeof("if errorlevel 1 color cf&echo ERROR happened when compare %2 with %3 !!(files are different) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n")-1);
	CCbat.Write("if errorlevel 2 color fd&echo ERROR happened when compare %2 with %3 !!(cannot open one of the files or invalid arguments or invalid switch) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n",sizeof("if errorlevel 2 color fd&echo ERROR happened when compare %2 with %3 !!(cannot open one of the files or invalid arguments or invalid switch) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n")-1);
	CCbat.Write("\r\n",sizeof("\r\n")-1);
	CCbat.Write("echo Start copy from %2 to %3: %copybgntime% %copybgndate%. >>C:\\%s%-%d%-%1.txt\r\n",sizeof("echo Start copy from %2 to %3: %copybgntime% %copybgndate%. >>C:\\%s%-%d%-%1.txt\r\n")-1);
	CCbat.Write("echo Finish copy from %2 to %3: %copyendtime% %copyenddate%. >>C:\\%s%-%d%-%1.txt\r\n",sizeof("echo Finish copy from %2 to %3: %copyendtime% %copyenddate%. >>C:\\%s%-%d%-%1.txt\r\n")-1);
	CCbat.Write("echo Finish comp from %2 to %3: %compendtime% %compenddate%. >>C:\\%s%-%d%-%1.txt\r\n",sizeof("echo Finish comp from %2 to %3: %compendtime% %compenddate%. >>C:\\%s%-%d%-%1.txt\r\n")-1);
	CCbat.Write("set info=%s%-%d%-%1-copy\r\n",sizeof("set info=%s%-%d%-%1-copy\r\n")-1);
	CCbat.Write("call %~dp0count %copybgntime% %copyendtime% C:\\%info%\r\n",sizeof("call %~dp0count %copybgntime% %copyendtime% C:\\%info%\r\n")-1);
	CCbat.Write("set info=%s%-%d%-%1-comp\r\n",sizeof("set info=%s%-%d%-%1-comp\r\n")-1);
	CCbat.Write("call %~dp0count %copyendtime% %compendtime% C:\\%info%\r\n",sizeof("call %~dp0count %copyendtime% %compendtime% C:\\%info%\r\n")-1);
	CCbat.Write("\r\n",sizeof("\r\n")-1);
	CCbat.Write("md D:\\%d%-%1-C\r\n",sizeof("md D:\\%d%-%1-C\r\n")-1);
	CCbat.Write("set copybgntime=%time%\r\n",sizeof("set copybgntime=%time%\r\n")-1);
	CCbat.Write("set copyenddate=%date%\r\n",sizeof("set copyenddate=%date%\r\n")-1);
	CCbat.Write("copy /Y %3 D:\\%d%-%1-C\r\n",sizeof("copy /Y %3 D:\\%d%-%1-C\r\n")-1);
	CCbat.Write("set copyendtime=%time%\r\n",sizeof("set copyendtime=%time%\r\n")-1);
	CCbat.Write("set copyenddate=%date%\r\n",sizeof("set copyenddate=%date%\r\n")-1);
	CCbat.Write("if errorlevel 1 color fc&echo ERROR happened when copy from %3 to D:\\%d%-%1-C !!(no files were found) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n",sizeof("if errorlevel 1 color fc&echo ERROR happened when copy from %3 to D:\\DataComp !!(no files were found) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n")-1);
	CCbat.Write("if errorlevel 4 color cf&echo ERROR happened when copy from %3 to D:\\%d%-%1-C !!(there is not enough memory) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n",sizeof("if errorlevel 4 color cf&echo ERROR happened when copy from %3 to D:\\DataComp !!(there is not enough memory) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n")-1);
	CCbat.Write("echo n|comp %2 D:\\%d%-%1-C\r\n",sizeof("echo n|comp %2 D:\\%d%-%1-C\r\n")-1);
	CCbat.Write("set compendtime=%time%\r\n",sizeof("set compendtime=%time%\r\n")-1);
	CCbat.Write("set compenddate=%date%\r\n",sizeof("set compenddate=%date%\r\n")-1);
	CCbat.Write("if errorlevel 1 color cf&echo ERROR happened when compare %2 with D:\\%d%-%1-C !!(files are different) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n",sizeof("if errorlevel 1 color cf&echo ERROR happened when compare %2 with D:\\DataComp !!(files are different) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n")-1);
	CCbat.Write("if errorlevel 2 color fd&echo ERROR happened when compare %2 with D:\\%d%-%1-C !!(cannot open one of the files or invalid arguments or invalid switch) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n",sizeof("if errorlevel 2 color fd&echo ERROR happened when compare %2 with D:\\DataComp !!(cannot open one of the files or invalid arguments or invalid switch) in loop %looptime% at %time% %date%>>C:\\error.txt &ping 127.0.0.1 -n 30>nul&goto l\r\n")-1);
	CCbat.Write("\r\n",sizeof("\r\n")-1);
	CCbat.Write("echo Start copy from %2 to D:\\%d%-%1-C: %copybgntime% %copybgndate%. >>C:\\%s%-%d%-%1.txt\r\n",sizeof("echo Start copy from %2 to D:\\%d%-%1-C: %copybgntime% %copybgndate%. >>C:\\%s%-%d%-%1.txt\r\n")-1);
	CCbat.Write("echo Finish copy from %2 to D:\\%d%-%1-C: %copyendtime% %copyenddate%. >>C:\\%s%-%d%-%1.txt\r\n",sizeof("echo Finish copy from %2 to D:\\%d%-%1-C: %copyendtime% %copyenddate%. >>C:\\%s%-%d%-%1.txt\r\n")-1);
	CCbat.Write("echo Finish comp from %2 to D:\\%d%-%1-C: %compendtime% %compenddate%. >>C:\\%s%-%d%-%1.txt\r\n",sizeof("echo Finish comp from %2 to D:\\%d%-%1-C: %compendtime% %compenddate%. >>C:\\%s%-%d%-%1.txt\r\n")-1);
	CCbat.Write("set info=%s%-%d%-%1-copy\r\n",sizeof("set info=%s%-%d%-%1-copy\r\n")-1);
	CCbat.Write("call %~dp0count %copybgntime% %copyendtime% C:\\%info%\r\n",sizeof("call %~dp0count %copybgntime% %copyendtime% C:\\%info%\r\n")-1);
	CCbat.Write("set info=%s%-%d%-%1-comp\r\n",sizeof("set info=%s%-%d%-%1-comp\r\n")-1);
	CCbat.Write("call %~dp0count %copyendtime% %compendtime% C:\\%info%\r\n",sizeof("call %~dp0count %copyendtime% %compendtime% C:\\%info%\r\n")-1);
	CCbat.Write("\r\n",sizeof("\r\n")-1);
	CCbat.Write("rd /s /q %3\r\n",sizeof("rd /s /q %3\r\n")-1);
	CCbat.Write("rd /s /q D:\\%d%-%1-C\r\n",sizeof("rd /s /q D:\\%d%-%1-C\r\n")-1);
	CCbat.Write("echo **************  Loop %looptime% has finished ***************** >>C:\\%s%-%d%-%1.txt\r\n",sizeof("echo **************  Loop %looptime% has finished ***************** >>C:\\%s%-%d%-%1.txt\r\n")-1);
	CCbat.Write("set /a looptime=looptime+1\r\n",sizeof("set /a looptime=looptime+1\r\n")-1);
	CCbat.Write("ping 127.0.0.1 -n 05>nul\r\n",sizeof("ping 127.0.0.1 -n 05>nul\r\n")-1);
	CCbat.Write("goto loop\r\n",sizeof("goto loop\r\n")-1);
	CCbat.Flush();
	CCbat.Close();

	GetTempPath(MAX_PATH,SysTmpPath);
	filename = SysTmpPath;
	filename+=_T("count.bat");
	iffind = finder.FindFile(filename);
	if(iffind)
	{
		CFile CCcount;
		CCcount.Remove(filename);
	}

	CFile Countbat(filename, CFile::modeCreate|CFile::modeWrite);

	Countbat.Write("set tmptime=%1\r\n",sizeof("set tmptime=%1\r\n")-1);
	Countbat.Write("if %tmptime:~2,1%==: (\r\n",sizeof("if %tmptime:~2,1%==: (\r\n")-1);
	Countbat.Write("set /a hour=%tmptime:~0,2%\r\n",sizeof("set /a hour=%tmptime:~0,2%\r\n")-1);
	Countbat.Write("if %tmptime:~3,1%==0 set /a min=%tmptime:~4,1%\r\n",sizeof("if %tmptime:~3,1%==0 set /a min=%tmptime:~4,1%\r\n")-1);
	Countbat.Write("if %tmptime:~3,1% NEQ 0 set /a min=%tmptime:~3,2%\r\n",sizeof("if %tmptime:~3,1% NEQ 0 set /a min=%tmptime:~3,2%\r\n")-1);
	Countbat.Write("if %tmptime:~6,1%==0 set /a sec=%tmptime:~7,1%\r\n",sizeof("if %tmptime:~6,1%==0 set /a sec=%tmptime:~7,1%\r\n")-1);
	Countbat.Write("if %tmptime:~6,1% NEQ 0 set /a sec=%tmptime:~6,2%)\r\n",sizeof("if %tmptime:~6,1% NEQ 0 set /a sec=%tmptime:~6,2%)\r\n")-1);
	Countbat.Write("if %tmptime:~1,1%==: (\r\n",sizeof("if %tmptime:~1,1%==: (\r\n")-1);
	Countbat.Write("set /a hour=%tmptime:~0,1%\r\n",sizeof("set /a hour=%tmptime:~0,1%\r\n")-1);
	Countbat.Write("if %tmptime:~2,1%==0 set /a min=%tmptime:~3,1%\r\n",sizeof("if %tmptime:~2,1%==0 set /a min=%tmptime:~3,1%\r\n")-1);
	Countbat.Write("if %tmptime:~2,1% NEQ 0 set /a min=%tmptime:~2,2%\r\n",sizeof("if %tmptime:~2,1% NEQ 0 set /a min=%tmptime:~2,2%\r\n")-1);
	Countbat.Write("if %tmptime:~5,1%==0 set /a sec=%tmptime:~6,1%\r\n",sizeof("if %tmptime:~5,1%==0 set /a sec=%tmptime:~6,1%\r\n")-1);
	Countbat.Write("if %tmptime:~5,1% NEQ 0 set /a sec=%tmptime:~5,2%)\r\n",sizeof("if %tmptime:~5,1% NEQ 0 set /a sec=%tmptime:~5,2%)\r\n")-1);
	Countbat.Write("set /a begin=%hour%*3600+%min%*60+%sec%\r\n",sizeof("set /a begin=%hour%*3600+%min%*60+%sec%\r\n")-1);
	Countbat.Write("\r\n",sizeof("\r\n")-1);
	Countbat.Write("set tmptime=%2\r\n",sizeof("set tmptime=%2\r\n")-1);
	Countbat.Write("if %tmptime:~2,1%==: (\r\n",sizeof("if %tmptime:~2,1%==: (\r\n")-1);
	Countbat.Write("set /a hour=%tmptime:~0,2%\r\n",sizeof("set /a hour=%tmptime:~0,2%\r\n")-1);
	Countbat.Write("if %tmptime:~3,1%==0 set /a min=%tmptime:~4,1%\r\n",sizeof("if %tmptime:~3,1%==0 set /a min=%tmptime:~4,1%\r\n")-1);
	Countbat.Write("if %tmptime:~3,1% NEQ 0 set /a min=%tmptime:~3,2%\r\n",sizeof("if %tmptime:~3,1% NEQ 0 set /a min=%tmptime:~3,2%\r\n")-1);
	Countbat.Write("if %tmptime:~6,1%==0 set /a sec=%tmptime:~7,1%\r\n",sizeof("if %tmptime:~6,1%==0 set /a sec=%tmptime:~7,1%\r\n")-1);
	Countbat.Write("if %tmptime:~6,1% NEQ 0 set /a sec=%tmptime:~6,2%)\r\n",sizeof("if %tmptime:~6,1% NEQ 0 set /a sec=%tmptime:~6,2%)\r\n")-1);
	Countbat.Write("if %tmptime:~1,1%==: (\r\n",sizeof("if %tmptime:~1,1%==: (\r\n")-1);
	Countbat.Write("set /a hour=%tmptime:~0,1%\r\n",sizeof("set /a hour=%tmptime:~0,1%\r\n")-1);
	Countbat.Write("if %tmptime:~2,1%==0 set /a min=%tmptime:~3,1%\r\n",sizeof("if %tmptime:~2,1%==0 set /a min=%tmptime:~3,1%\r\n")-1);
	Countbat.Write("if %tmptime:~2,1% NEQ 0 set /a min=%tmptime:~2,2%\r\n",sizeof("if %tmptime:~2,1% NEQ 0 set /a min=%tmptime:~2,2%\r\n")-1);
	Countbat.Write("if %tmptime:~5,1%==0 set /a sec=%tmptime:~6,1%\r\n",sizeof("if %tmptime:~5,1%==0 set /a sec=%tmptime:~6,1%\r\n")-1);
	Countbat.Write("if %tmptime:~5,1% NEQ 0 set /a sec=%tmptime:~5,2%)\r\n",sizeof("if %tmptime:~5,1% NEQ 0 set /a sec=%tmptime:~5,2%)\r\n")-1);
	Countbat.Write("set /a final=%hour%*3600+%min%*60+%sec%\r\n",sizeof("set /a final=%hour%*3600+%min%*60+%sec%\r\n")-1);
	Countbat.Write("\r\n",sizeof("\r\n")-1);
	Countbat.Write("set /a total=%final%-%begin%\r\n",sizeof("set /a total=%final%-%begin%\r\n")-1);
	Countbat.Write("set info=%3\r\n",sizeof("set info=%3\r\n")-1);
	Countbat.Write("echo total %info% time: %total% seconds >>%info:~0,-5%.txt\r\n",sizeof("echo total %info% time: %total% seconds >>%info:~0,-5%.txt\r\n")-1);
	Countbat.Write("echo --                            >>%info:~0,-5%.txt\r\n",sizeof("echo --                            >>%info:~0,-5%.txt\r\n")-1);
	Countbat.Flush();
	Countbat.Close();

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}