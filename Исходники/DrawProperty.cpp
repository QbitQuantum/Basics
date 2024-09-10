//--------------------------------------------------------------------------
//　다이얼로그 초기화
//--------------------------------------------------------------------------
BOOL CDrawProperty::OnInitDialog()
{
	CDialog::OnInitDialog();

	//////////////////////////////////////////////////////////////////////////
	//라인 굵기 스핀 컨트롤 초기화
	m_sLineWeightSpin.SetRange(1,30);	//최소 두께 1~최대 두께 30
	m_sLineWeightSpin.SetPos(1);		//기본 값 1
	
	//////////////////////////////////////////////////////////////////////////
	//알파값 스핀 컨트롤 초기화
	m_sAlphaSpin.SetRange(1, 100);	//최소 불투명도 1% ~ 최대 불투명도 100%
	m_sAlphaSpin.SetPos(100);		//기본값 100

	//////////////////////////////////////////////////////////////////////////
	//　라인 패턴 콤보 박스 초기화
	for(int i=0; i<5; i++)
		m_sLinePtnCombo.AddItem(i, LINEPATTERN);
	m_sLinePtnCombo.SetCurSel(0);

	//////////////////////////////////////////////////////////////////////////
	//브러쉬 패턴 콤보 박스 초기화
	for(int i=0; i<52; i++)
		m_sFillPtnCombo.AddItem(i, HATCHPATTERN);
	m_sFillPtnCombo.SetCurSel(0);
	
	//////////////////////////////////////////////////////////////////////////
	//선 시작-끝 모양 콤보박스 초기화
	m_sStartCapCombo.SetCurSel(1);
	m_sEndCapCombo.SetCurSel(1);

	//////////////////////////////////////////////////////////////////////////
	//외곽선 모양 콤보 박스 초기화
	m_sLineJoinCombo.SetCurSel(0);

	//////////////////////////////////////////////////////////////////////////
	// 그라디언트 콤보 박스 초기화
	for(int i=0; i<4; i++)
		m_sGradientCombo.AddItem(i, GRADIENTPATTERN);
	m_sGradientCombo.SetCurSel(0);

	//////////////////////////////////////////////////////////////////////////
	// 면 타입 라디오 버튼 초기화
	m_sFaceTypeOutlinedFill.SetCheck(1);
	m_sFaceTypeOutline.SetCheck(0);

	m_sFillTypeSolid.SetCheck(1);
	m_sFillTypeHatch.SetCheck(0);
	m_sFillTypeGradient.SetCheck(0);

	m_sGradientEndColorBtn.EnableWindow(FALSE);


	//////////////////////////////////////////////////////////////////////////
	//　윈도우 비스타 이상에서는 라디오버튼에 XP 테마 적용이 제대로 되지 않는 문제 해결을 위해 추가
	OSVERSIONINFO sInfo;
	sInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	// 윈도우 버전 정보를 구해 비스타 이상일 경우 아래 내용 적용
	if(::GetVersionEx(&sInfo) && (sInfo.dwPlatformId == VER_PLATFORM_WIN32_NT && sInfo.dwMajorVersion >= 6 && sInfo.dwMinorVersion >= 0))
	{
		SetWindowTheme(GetDlgItem(IDC_FACE_FILL)->GetSafeHwnd(), L"", L"");
		SetWindowTheme(GetDlgItem(IDC_FACE_ONLYFILL)->GetSafeHwnd(), L"", L"");
		SetWindowTheme(GetDlgItem(IDC_FACE_OUTLINED)->GetSafeHwnd(), L"", L"");
		SetWindowTheme(GetDlgItem(IDC_FILLTYPE_GRADIENT)->GetSafeHwnd(), L"", L"");
		SetWindowTheme(GetDlgItem(IDC_FILLTYPE_HATCH)->GetSafeHwnd(), L"", L"");
		SetWindowTheme(GetDlgItem(IDC_FILLTYPE_SOLID)->GetSafeHwnd(), L"", L"");
	}

	//////////////////////////////////////////////////////////////////////////
	// 툴팁 컨트롤 초기화
	CMFCToolTipInfo params;
	params.m_bBoldLabel = TRUE;
	params.m_bDrawDescription = TRUE;
	params.m_bDrawIcon = TRUE;
	params.m_bRoundedCorners = TRUE;
	params.m_bDrawSeparator = FALSE;
	params.m_clrFill = RGB (255, 255, 255);
	params.m_clrFillGradient = RGB (228, 228, 240);
	params.m_clrText = RGB (61, 83, 80);
	params.m_clrBorder = RGB (144, 149, 168);
	m_sCtrlToolTip.SetParams(&params);

	m_sCtrlToolTip.Create(this);
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_BUTTON_FONT), L"폰트");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_BUTTON_LINECOLOR), L"라인색(텍스트색)");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_BUTTON_FILLCOLOR), L"채우기색");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_BUTTON_FILLCOLOR2), L"그라디언트 채우기색");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_FACE_OUTLINED), L"외곽선만 그리기");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_FACE_FILL), L"외곽선+채우기");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_FACE_ONLYFILL), L"내부만 채우기");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_FILLTYPE_SOLID), L"단색으로 채우기");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_FILLTYPE_HATCH), L"격자무늬 채우기");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_FILLTYPE_GRADIENT), L"그라디언트 채우기");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_COMBO_STARTCAP), L"라인 시작 모양");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_COMBO_ENDCAP),L"라인 끝 모양");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_EDIT_LINEWEIGHT), L"라인 굵기");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_SPIN1), L"라인 굵기");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_LINEPATTERN), L"라인 패턴");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_COMBO_LINEJOIN), L"외곽선 처리");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_FILLPATTERN), L"채우기 패턴");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_EDIT_ALPHA), L"불투명도");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_SPIN2), L"불투명도");
	m_sCtrlToolTip.AddTool(GetDlgItem(IDC_COMBO_GRADIENT), L"그라디언트 패턴");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}