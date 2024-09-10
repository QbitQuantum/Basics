BOOL CSpotsMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标



	// TODO:  在此添加额外的初始化代码
	// 打开控制台
	if (__argc > 1)
	{ 
		for (size_t i = 0; i < __argc; i++)
		{
			CString targv = __targv[i];
			if (targv == L"debug")//输出命令台 
			{
				MFCConsole::Init();
				MFCConsole::Output("Debug start.\r\n");
			}
			if (targv == L"virtual")
			{
				p_contrller->IsRealModel = 0;
			}
		}
	}
	//p_contrller->IsRealModel = 0;
	// 添加菜单栏
	ModifyStyle(WS_THICKFRAME, DS_MODALFRAME);
	menu.LoadMenuW(IDR_MenuMain);
	SetMenu(&menu);

	int Standard_Width_mm = 0;
	if (SettingHelper::GetKeyInt("SYS_IMG_CAPTURE", "Standard_Width_mm", Standard_Width_mm))
		GetDlgItem(IDC_TB_Real_WidthMM)->SetWindowText(StringHelper::int2CString(Standard_Width_mm));
	else
		GetDlgItem(IDC_TB_Real_WidthMM)->SetWindowText(L"600");

	int Standard_Length_mm = 0;
	if (SettingHelper::GetKeyInt("SYS_IMG_CAPTURE", "Standard_Length_mm", Standard_Length_mm))
		GetDlgItem(IDC_TB_Real_LengthMM)->SetWindowText(StringHelper::int2CString(Standard_Length_mm));
	else
		GetDlgItem(IDC_TB_Real_LengthMM)->SetWindowText(L"300");

	//系统初始化
	p_contrller->Init();



	CSliderCtrl *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_IMG_X);
	pSlidCtrl->EnableWindow(0);
	pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_IMG_Y);
	pSlidCtrl->EnableWindow(0);
	pSlidCtrl = 0;

	/***************保存控件初始位置，用于自适应窗口缩放******************/
	save1control(0);//保存主窗口
	
	save1control(IDC_BTN_SelectVirtualImg);
	save1control(IDC_BTN_virtualTigger);
	save1control(IDC_BTN_TriggerContinue);
	save1control(IDC_BTN_PlaneArray);
	save1control(IDC_BTN_PlaneArraySolo);
	save1control(IDC_BTN_RUN);
	save1control(IDCANCEL);
	save1control(IDC_GB_IMG_BIG);
	save1control(IDC_IMG_BIG);
	save1control(IDC_LABLE_IMG_INFO);
	save1control(IDC_SLIDER_IMG_X);
	save1control(IDC_SLIDER_IMG_Y);

	save1control(IDC_GB_LogImg);
	save1control(IDC_IMG_HISTORY);

	save1control(IDC_GB_STATISTIC);
	save1control(IDC_LB11);
	save1control(IDC_LB7);
	save1control(IDC_LB8);
	save1control(IDC_LB9);
	save1control(IDC_LB10);
	save1control(IDC_LB12);
	save1control(IDC_LB4);
	save1control(IDC_LB5);
	save1control(IDC_LB6);


	save1control(IDC_LB_todayTotal);
	save1control(IDC_LB_todayA);
	save1control(IDC_LB_todayB);
	save1control(IDC_LB_todayC);
	save1control(IDC_LB_todayGood);
	save1control(IDC_LB_dayFineRate);

	save1control(IDC_LB_monthTotal);
	save1control(IDC_LB_monthA);
	save1control(IDC_LB_monthB);
	save1control(IDC_LB_monthC);
	save1control(IDC_LB_monthGood);
	save1control(IDC_LB_monthFineRate);

	save1control(IDC_LB_yearTotal);
	save1control(IDC_LB_yearA);
	save1control(IDC_LB_yearB);
	save1control(IDC_LB_yearC);
	save1control(IDC_LB_yearGood);
	save1control(IDC_LB_yearFineRate);

	save1control(IDC_LB_SIZESHOW);
	save1control(IDC_GB_SIZE);
	save1control(IDC_LB_SZIE_X);
	save1control(IDC_TB_Real_WidthMM);
	save1control(IDC_LB_SIZE_Y);
	save1control(IDC_TB_Real_LengthMM);
	save1control(IDC_BTN_SizeDingBiao);
	save1control(IDC_MAIN_DINGBIAO);

	string MainHSVs;
	if (SettingHelper::GetKeyString("AreaCam", "MainHSVs", MainHSVs))
		GetDlgItem(IDC_MAIN_HSV)->SetWindowText(StringHelper::string2CString(MainHSVs));
	else
		GetDlgItem(IDC_MAIN_HSV)->SetWindowText(L"300");

	FileStorage fs("data//histdata.yaml", FileStorage::READ);//历史样本图片导入
	fs["hissample"] >> SampleImg_cache;
	fs.release();
	if (SampleImg_cache.empty())
		SampleImg_cache = Mat(70, 10, CV_8UC1, Scalar(255));
	
	initEndFlag = true;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE 
}