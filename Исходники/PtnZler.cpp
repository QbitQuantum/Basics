void CPtnZler::OnMenuPattern()
{
	if (!IsBoardLegal())
	{
		window->MessageBox(L"盘面不合法", L"定形局", MB_ICONWARNING | MB_OK);
		return;
	}
	if (window->MessageBox(L"确定以当前盘面进行创作？", L"定形局", MB_ICONQUESTION | MB_OKCANCEL) != IDOK)
		return;

	g_pGameTable->SetZlerBase(this);
	g_pGameTable->SetAction(0);

	//进入Pattern目录
	TCHAR wcsPatternPath[_MAX_PATH];
	wsprintf(wcsPatternPath, L"%s\\Pattern", ModulePath);
	if (_waccess(wcsPatternPath, 0) == -1)
		_wmkdir(wcsPatternPath);
	_wchdir(wcsPatternPath);
	//创建文件夹
	time_t t = time(NULL);
	wcsftime(m_wcsTimeFolder, sizeof(m_wcsTimeFolder) / sizeof(TCHAR), L"%Y%m%d_%H%M%S", localtime(&t)); //Eg: 20130814_210517
	_wmkdir(m_wcsTimeFolder);
	//设置起始文件号
	m_nFileNumber = 1;
	if (!SavePtnTitle(wcsPatternPath))
		return;

	InitSwapRemain();
	ProcessPattern(true);
}