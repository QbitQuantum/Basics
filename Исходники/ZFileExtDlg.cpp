bool ZFileExtDlg::SetExtWithProgram(const tstring & strProgramName, const tstring & strExt, tstring strFullProgramPath, const tstring & strIcon, int iIconIndex)
{
	ZFileExtReg fileExtReg;


	if ( strFullProgramPath.empty() )
	{
		// get full file path to program executable file
		TCHAR szProgPath[MAX_PATH] = { 0 };
		::GetModuleFileName(NULL, szProgPath, sizeof(szProgPath) / sizeof(TCHAR));

		strFullProgramPath = szProgPath;
	}

	tstring strTempText;

	fileExtReg.m_strExtension = strExt.c_str();

	// 프로그램에게 인자를 넘겨줄 때의 full path 를 만든다.
	strTempText  = strFullProgramPath;
	strTempText += TEXT(" \"%1\"");
	fileExtReg.m_strShellOpenCommand = strTempText.c_str();
	fileExtReg.m_strDocumentShellOpenCommand = strTempText.c_str();

	// 레지스트리에 등록할 때의 프로그램의 이름과 확장자를 정한다.
	tstring strClassName = strProgramName;
	strClassName += TEXT(".");
	strClassName += strExt;
	fileExtReg.m_strDocumentClassName = strClassName.c_str();

	// 확장자에 맞는 기본 아이콘을 지정한다.
	if ( strIcon.size() <= 0 )
	{
		// 아이콘 프로그램을 지정하지 않으면 원래 프로그램의 첫번째 아이콘을 쓴다.
		strTempText  = strFullProgramPath;
		strTempText += TEXT(",0");
	}
	else
	{
		// 아이콘 프로그램을 지정했으면 icon 번호를 쓴다.
		if ( iIconIndex < 0 )
		{
			assert(iIconIndex >= 0 );
			iIconIndex = 0;
		}

		strTempText = strIcon;
		strTempText += TEXT(",");

		TCHAR szTemp[COMMON_BUFFER_SIZE] = { 0 };
		SPrintf(szTemp, COMMON_BUFFER_SIZE, TEXT("%d"), iIconIndex);
		strTempText += szTemp;
	}
	fileExtReg.m_strDocumentDefaultIcon = strTempText.c_str();

	// 설정된 값으로 레지스트리를 등록한다.
	fileExtReg.SetRegistries();

	return true;
}