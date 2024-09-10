BOOL CUpdaterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CSVPToolBox svpTool;
	CString szLangDefault = svpTool.GetPlayerPath(  _T("lang\\default") );
	CString szLangSeting;
	m_nLanguage = 0;
		BOOL langSeted = false;
		//get default lang setting

		if(svpTool.ifFileExist(szLangDefault)){
			szLangSeting = svpTool.fileGetContent(szLangDefault);
			if(!szLangSeting.IsEmpty()){
				m_nLanguage = _wtoi( szLangSeting );
				langSeted = true;
			}
		}
		if(!langSeted){
			
			switch(GetSystemDefaultLangID()){ //http://www.science.co.il/Language/Locale-Codes.asp?s=codepage
					case 0x0804:
					case 0x1004:
					case 0x1404:
					case 0x0c04:
					case 0x0404: //Chinese 
						m_nLanguage = 0;
						break;
					default:
						m_nLanguage = 1;
						break;
			}
			
		}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	prg_total.SetRange(0, 1000);
	
	HDC hdc = ::GetDC(NULL);
	double dDefaultSize = 22;
	double dIntroSize = 14;
	m_scale = (double)GetDeviceCaps(hdc, LOGPIXELSY) / 96.0;
	double scale = 1.0;
	::ReleaseDC(0, hdc);

	m_hBigFont.m_hObject = NULL;
	

	if(!(::GetVersion()&0x80000000)){
		m_hBigFont.CreateFont(int(dDefaultSize * scale), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, 
		_T("Microsoft Sans Serif"));

		m_hIntroFont.CreateFont(int(dIntroSize * scale), 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, 
			_T("Microsoft Sans Serif"));
	}
	if(!m_hBigFont.m_hObject){
		m_hBigFont.CreateFont(int(dDefaultSize * scale), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, 
		_T("MS Sans Serif"));


		m_hIntroFont.CreateFont(int(dIntroSize * scale), 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, 
			_T("MS Sans Serif"));

	}
	tnid.cbSize = sizeof(NOTIFYICONDATA); 
	tnid.hWnd = this->m_hWnd; 
	tnid.uID = IDR_MAINFRAME; 
	tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; 
	tnid.uCallbackMessage = WM_NOTIFYICON; 
	tnid.hIcon = this->m_hIcon; 

	if(m_nLanguage ){
		SetWindowText(L"SPlayer Updater");
		csCurTask.SetWindowText(L"Current Task:");
		csTotalProgress.SetWindowText(L"Total:");
		szSpeed.SetWindowText(L"Speed:");
		cb_stop.SetWindowText(L"Cancel");
		cslink.SetWindowText(L"<a href=\"http://blog.splayer.org\">ChangeLog...</a>");
		cszSizeTotal.SetWindowText(L"Size:");
		
		cs_stat.SetWindowText(_T("This program will update lastest SPlayer, will exit automaticly after finished."));
		csCurTask.SetWindowText(_T("Current Task: Calc..."));
		wcscpy_s(tnid.szTip, _T("SPlayer Auto Updater"));

		szaIntro.Add(L"SPlayer support DXVA、DXVA2、EVR");

		szaIntro.Add(_T("SPlayer optimization of a variety of creative techniques, smooth playback. Maximize the efficiency are always our mission "));
		szaIntro.Add(_T("SPlayer mainly focused on user experience"));
		szaIntro.Add(_T("SPlayer is an open source software "));
		szaIntro.Add(_T("Designer Raven from Milan created a set of interfaces. Beautiful skin can let you feel more comfortable while playing"));
		szaIntro.Add(_T("SPlayer is world's smallest and most sophisticated players, complete installation package only 5M, still as powerful as ever ..."));
		szaIntro.Add(_T("SPlayer origin from MPCHC ffmpeg and thanks everyone with them"));
		szaIntro.Add(_T("SPlayer can download subtitle aotomaticely, you can disable it in setting panel if you want"));

	}else{
		cs_stat.SetWindowText(_T("本程序下载最新版的射手播放器，将在更新完成后5分钟内退出"));
		csCurTask.SetWindowText(_T("当前任务：正在计算下载量"));
		wcscpy_s(tnid.szTip, _T("射手影音播放器自动更新程序"));

		szaIntro.Add(_T("只要在设置中启用“智能拖拽”，鼠标拖住画面就可以方便的改变画面比例"));
		szaIntro.Add(_T("在界面设置中可以设置自定义的背景界面"));
		szaIntro.Add(_T("射手播放器无需安装额外解码包即可全能解码"));

		szaIntro.Add(_T("免配置智能启用硬件高清加速：DXVA、DXVA2、EVR和CUDA"));
		szaIntro.Add(_T("十余种画面效果功能组合，全新的视频观赏体验。"));
		szaIntro.Add(_T("全自动网络字幕匹配。抛弃浏览器，也不必再收集。只要一人播放过且同意共享，全球华人都可在播放时得到恰好匹配影片的字幕。"));
		szaIntro.Add(_T("双字幕显示，同时显示中英双语，共同学习提高。"));
		szaIntro.Add(_T("绿色版免安装，同时支持海量视频格式，永不流氓！"));
		szaIntro.Add(_T("与众不同的字幕默认字体与颜色，对抗视觉疲劳。"));
		szaIntro.Add(_T("智能识别简体或繁体字幕。告别乱码，也不用再手动转码。"));
		szaIntro.Add(_T("自动减小英文字码，双语字幕更美观优雅。"));
		szaIntro.Add(_T("根据使用习惯优化右键菜单，方便快速切换字幕和显示模式。"));
		szaIntro.Add(_T("更加易用、精简的控制面板，更方便且易于理解的设置选项。"));
		szaIntro.Add(_T("自动升级随时更新最新版本、体验最新功能。"));
		szaIntro.Add(_T("射手播放器拥护GPL授权协议，是开源软件。"));

	}

	SetTimer(IDT_START_CHECK, 1000, NULL);



	
	Shell_NotifyIcon(NIM_ADD, &tnid); 



	
	if(bHide){
		ShowWindow(SW_MINIMIZE);
		ShowWindow(SW_HIDE);

	}else{
		notYetShow = false;
		ShowWindow(SW_SHOW);
		ShowWindow(SW_RESTORE);
	}
	
	return FALSE;  // return TRUE  unless you set the focus to a control
}