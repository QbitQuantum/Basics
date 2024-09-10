void CBkInfoDownloadManager::MyBankUsbKeyDownload(LPUSBRECORD pUsbNode) // 下载USBKEY// LPSTR lpBankID, LPVOID lpVoid, int nSize
{
	std::string strBankID = pUsbNode->fav;
	std::string strXml = pUsbNode->xml;
	std::string strVer = pUsbNode->ver;

	//检测银行控件是否已经安装
	CBankData* pBankData = CBankData::GetInstance();

	// 2者条件满足一个就进行安装
	bool bAddBkCtrl = false;
	CBkInfoDownloadManager* pManager = CBkInfoDownloadManager::GetInstance ();
	bool bSetup = pManager->IsSetupAlready (pUsbNode->fav);
	bool bExist = pBankData->IsFavExist(strBankID);
	if ((!bSetup) || (!bExist))
	{
		m_bAddBkCtrl = true; // 标记下载的银行控件是USBKEY触发的
		CNotifyFavProgress::GetInstance()->AddFav(pUsbNode->fav);//调用js开始安装
		
		bAddBkCtrl = true;
	}

	// 得到USBKEY保存的名字，VID+PID+MID
	std::wstring strSaveName;
	wchar_t wchTemp[20] = {0};
	_itow_s (pUsbNode->vid, wchTemp, 19, 10);
	strSaveName += wchTemp;
	memset (wchTemp, 0, sizeof (wchTemp));
	_itow_s (pUsbNode->pid, wchTemp, 19, 10);
	strSaveName += wchTemp;
	memset (wchTemp, 0, sizeof (wchTemp));
	_itow_s (pUsbNode->mid, wchTemp, 19, 10);
	strSaveName += wchTemp;

	// 得到ID的下载控件对象指针
	CDownloadManagerThread* pTempThread = FindBankCtrlDLManager((LPSTR)strBankID.c_str ());
	if (NULL == pTempThread)
	{
		pTempThread = new CDownloadManagerThread (); // 创建一个管理对象

		::EnterCriticalSection(&m_cs);
		m_BankManager.insert (std::make_pair (strBankID.c_str (), pTempThread)); // 将新生成的加入到map
		::LeaveCriticalSection (&m_cs);
	}
	std::wstring strXmlPath, strCtrlPath;
	if (m_wstrDLTempPath.empty ())
		m_wstrDLTempPath = GetTempCachePath (); // 得到下载的临时路径

	strXmlPath = m_wstrDLTempPath;
	strCtrlPath = m_wstrDLTempPath;

	strXmlPath += strSaveName;
	strXmlPath += L".xml";
	strCtrlPath += strSaveName;
	strCtrlPath += L".exe";

	//做base64编码
	DWORD dwBufLen = strlen(strXml.c_str()) + 32;
	LPSTR lpszXmlInfo = new char[dwBufLen];

	strcpy_s(lpszXmlInfo,dwBufLen,strXml.c_str());

	int dwSize = strlen(lpszXmlInfo) * 2 + 1;
	unsigned char* pszOut = new unsigned char[dwSize];
	base64_encode((LPBYTE)lpszXmlInfo, strlen(lpszXmlInfo), pszOut, &dwSize);
	pszOut[dwSize] = 0;


	strXml = "xml=";
	strXml += UrlEncode((char *)pszOut);

	// 从服务器端下载检验码和下载连接（采用阻塞方式下载，没有创建新的线程下载,因为要校验码）
	std::wstring downPath = CHostContainer::GetInstance()->GetHostName(kWeb);
	downPath += CA2W(MONEYHUB_USBKEY_URL);
	DOWN_LOAD_PARAM_NODE myNode;
	myNode.bCreateThread = false;
	myNode.strHWID = m_strHWID;
	myNode.strSendData = strXml;
	//myNode.dwPostDataLength = strXml.size ();
	myNode.strSaveFile = strXmlPath;
	myNode.strUrl = downPath;

	
	if (!pTempThread->CreateDownLoadTask (&myNode))
	{
		CRecordProgram::GetInstance()->FeedbackError(MY_ERROR_PRO_CORE, ERR_DOWNLOAD_XML_USBKEY, L"MyBankUsbKeyDownload从服务器端下载XML文件失败！");
	}

	// 检验验证码，并得到下载连接
	std::string strNewCk;
	std::string strVersion;
	std::list<std::wstring> UrlList;
	if (!CheckUsbKeyXml(strXmlPath.c_str (), UrlList, strNewCk, strVersion))
	{
		CRecordProgram::GetInstance()->FeedbackError(MY_ERROR_PRO_CORE, ERR_READ_XML_USBKEY, CRecordProgram::GetInstance()->GetRecordInfo(L"MyBankUsbKeyDownload解析%s数据失败！",strXmlPath.c_str ()));
	}

	bool bUpData = false;
	// 进行版本比较
	int nVerComp = MyTwoVersionCompare (strVersion, strVer);
	// 表示要弹出版本要更新的提示
	if (nVerComp > 0)
		bUpData = true;
	if(strVer == DEFAULT_INSTALL_VERSION)
	{
		bUpData = false;
	}


	// 检验该usb控件是否已经安装，没有安装就下载安装
	bool bCheck = m_staticpICheckFile->CheckServerXmlFile (bUpData, *pUsbNode);
	if(bCheck == false)
		return;
	int nStatus = pUsbNode->status; // 用这个来判定是否安装
	if (200 == nStatus)
	{
		// 如果银行控件已经收藏
		if (bAddBkCtrl == false || bSetup == true || bUpData == false)
		{
			USBKeyInfo* pusb = CUSBHardWareDetector::GetInstance()->CheckUSBHardWare(pUsbNode->vid, pUsbNode->pid, pUsbNode->mid);//从内存文件中获得相关信息

			if(!pusb)
				return;

			wstring msg;
			msg = pusb->hardware.goodsname + L"软件安装正常，可以使用";
			mhShowMessage( GetActiveWindow(), msg.c_str());

			return;
		}
	}
 
	// 更新USBKEY的版本
	CBankData::GetInstance ()->UpdateUSB (pUsbNode->vid, pUsbNode->pid, pUsbNode->mid, strVersion);


	if (UrlList.size() <= 0)
	{
		CRecordProgram::GetInstance()->FeedbackError(MY_ERROR_PRO_CORE, ERR_DOWNLOAD_URL_NOFOUND_USBKEY, L"MyBankUsbKeyDownload没有检测到下载链接！");
	}

	std::list<std::wstring>::iterator it;
	for (it = UrlList.begin (); it != UrlList.end (); it ++) // 创建下载任务
	{
		DOWN_LOAD_PARAM_NODE myNode;
		myNode.bCreateThread = true;
		myNode.strHWID = m_strHWID;
		myNode.emKind = emUsbKey; // 下载USBKEY
		
		myNode.strSetupPath = m_wstrSetupPath;
		myNode.bSetupDlFile = true;
		myNode.strSaveFile = strCtrlPath;
		myNode.strUrl = (*it);

		// 初始化USBKEY特有的参数
		myNode.dwUsbKeyParam.nMid = pUsbNode->mid;
		myNode.dwUsbKeyParam.nPid = pUsbNode->pid;
		myNode.dwUsbKeyParam.nVid = pUsbNode->vid;
		myNode.dwUsbKeyParam.strVersion = pUsbNode->ver;


		pTempThread->CreateDownLoadTask (&myNode);
		
	}

}