BOOL CProcessMgr::Open(CString sProcessFilePath)
{
	ZTools::WriteZToolsFormatLog("开始打开设计过程");
/*
建目录
解压
存工作路径变量
打开建模页面
*/
	if (sProcessFilePath.IsEmpty())
	{
		return FALSE;
	}

	//创建临时目录
	CString sWorkPath = GetExecDir() + "\\Data\\" + ReslibMgr::GuidToString(ReslibMgr::CreateGuid()).c_str();

	if (!MakeSureDirectoryPathExists(sWorkPath + "\\"))
	{
		ZTools::WriteZToolsFormatLog("创建工作目录失败：%s", sWorkPath);
		return FALSE;
	}

	//解压
	if (!ZipTool::Unzip((LPCTSTR)sProcessFilePath, (LPCTSTR)sWorkPath))
	{
		ZTools::WriteZToolsFormatLog("unzip file failed: %s", sProcessFilePath);
		return FALSE;
	}

	//打开建模页面
	CMainFrame * pMainFrame = reinterpret_cast< CMainFrame * > ( theApp.m_pMainWnd );
	if (!pMainFrame)
	{
		return FALSE;
	}
	pMainFrame->OnMenuModuleOpenjianmo();

	CDlgSvg * pSvg = GetSvgDilogPtr();
	if ( pSvg == NULL ) return FALSE;

	//设置当前设计过程的变量
	Clear();
	m_sProcessFilePath = sProcessFilePath;
	m_sWorkPath = sWorkPath;
	
	{//打开时同样添加历史记录
		CString strHistoryPath = m_sWorkPath + "\\main.xpdl";
		if ( !IsAccessibleFile( strHistoryPath ) )
		{
			return FALSE;
		}

		TiXmlBase::SetCondenseWhiteSpace(false);
		TiXmlDocument doc;
		doc.LoadFile(strHistoryPath, TIXML_ENCODING_UTF8);
		if (doc.Error())
		{
			ZTools::WriteZToolsFormatLog("解析main.xpdl出错");
			return FALSE;
		}
		TiXmlElement* rootElement = doc.RootElement();//Package
		if (rootElement)
		{
			std::string strName;
			std::string strValue;
			//rootElement->QueryStringAttribute("name", &strName);
			TiXmlAttribute* pAb;
			pAb = rootElement->FirstAttribute();
			while (pAb)
			{
				strName = pAb->Name();
				strValue = pAb->Value();
				ZTools::UTF8ToMB(strName);
				ZTools::UTF8ToMB(strValue);
				if(strName == "Name")
				{
					AddToHistory(strValue.c_str(), m_sProcessFilePath);//添加到历史
					theApp.GetMainWnd()->SetTimer( TIMER_MAINFRAME_RECENTLYMENU, TIMER_MAINFRAME_RECENTLYMENU_TIMEOUT, 0);
					break;
				}
				pAb = pAb->Next();
			}			
		}
	}

	ZTools::WriteZToolsFormatLog("工作路径准备完成，开始加载静态页面");
	pSvg->Navigate( theGlobalConfig.m_strSvgUrl );
	return TRUE;
}