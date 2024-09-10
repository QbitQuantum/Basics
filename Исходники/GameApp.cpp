bool CGameApp::Init()
{	
// plasma 2005.07.06 - 디버그 모드에선 그냥 직접 읽고, 릴리즈 모드에선 pak 파일에서 추출해서 사용한다.
#ifdef _DEBUG
//	if( !g_TextManager.Load("text_data/text.dat") ) 
	if( !g_TextManager.LoadPack("text.dat", "text_data") ) 
	{
		MessageBox( NULL, "Text.Dat load fail", "Error", MB_OK );
	}
#else
	if( !g_TextManager.LoadPack("text.dat", "text_data") ) 
	{
		MessageBox( NULL, "Text.Dat load fail", "Error", MB_OK );
	}
#endif
	
	// Create game all systems.
	m_pGSystem  = new CSystemWin32Imp;
	m_pGSystem->Init(m_pProcessInfo);

	// 2003/11/19 by impurity create xml system
	MSXML2::IXMLDOMDocument2Ptr pDoc = NULL;
//#ifdef _DEBUG
//	CFileSys::ConvertBinaryXML("script\\window.xml","script\\window.bml");
//	FILE* fIn;
//	if(NULL!=(fIn=fopen("script\\window.bml","rb")))
//	{
//		CFileSys::LoadBinaryXML(pDoc, fIn);
//	}	
//	fclose( fIn );
//#else 
	DFileGPack packFile;
	packFile.Open(SFullName("script","window.bml"));
	CFileSys::LoadBinaryXML(pDoc, packFile.GetFile(), packFile.GetSize());
	packFile.Close();
//#endif
	
	
	MSXML2::IXMLDOMNodePtr pNode = NULL;
	
	if(pNode=pDoc->selectSingleNode(L"./root/window/bitperpixel"))
	{
		m_DisplayMode.iBitPerPixel = (short)pNode->GetnodeTypedValue();
	}
	else
	{
		m_DisplayMode.iBitPerPixel = 16;
	}
	
	m_DisplayMode.iDeviceType = 0;
	
	//if(pNode=pDoc->selectSingleNode(L"./root/window/fullmode"))
	//{
	//	m_DisplayMode.iFullScreen = (bool)pNode->GetnodeTypedValue();
	//	((CProcessInfoWin32Imp *)m_pProcessInfo)->m_bFullScreen = true;
	//}
	//else
	{
		m_DisplayMode.iFullScreen = false;
		((CProcessInfoWin32Imp *)m_pProcessInfo)->m_bFullScreen = false;
	}
	
	m_DisplayMode.iRefreshRate = 0;
	m_DisplayMode.iZBufferDepth = 32;
	
	if(pNode=pDoc->selectSingleNode(L"./root/window/width"))
	{
		m_DisplayMode.iWidth = (short)pNode->GetnodeTypedValue();
	}
	else
	{
		m_DisplayMode.iWidth = 800;
	}
	
	if(pNode=pDoc->selectSingleNode(L"./root/window/height"))
	{
		m_DisplayMode.iHeight = (short)pNode->GetnodeTypedValue();
	}
	else
	{
		m_DisplayMode.iHeight = 600;
	}
	
	CFileSys::UnloadXML(pDoc);
	


	m_pGameFactory = new CGameFactoryImp;
	// Register Game factory to Factory System.
	m_pGSystem->GetFactorySys()->RegisterGameFactory( m_pGameFactory );


	// 3d base initial.
	InitPhysics();

	CWindowSysWin32Imp* pWindowSysWin32Imp = (CWindowSysWin32Imp*)m_pGSystem->GetWindowSys();

	if( !m_pGSystem->GetGControlSys()->Create( pWindowSysWin32Imp->m_hWnd, 
		                                       m_DisplayMode ) )
	{
		// Device create error 
		DLogWriteSystem("Create Device Error");
		Shutdown();
	}

	int Xplus = GetSystemMetrics(SM_CXBORDER)*2*GetSystemMetrics(SM_CXFIXEDFRAME);
	int Yplus = GetSystemMetrics(SM_CYBORDER)*2*GetSystemMetrics(SM_CYFIXEDFRAME) +
				GetSystemMetrics(SM_CYCAPTION);
	SetWindowPos(pWindowSysWin32Imp->m_hWnd, HWND_NOTOPMOST, (GetSystemMetrics(SM_CXSCREEN)-m_DisplayMode.iWidth)/2,
				(GetSystemMetrics(SM_CYSCREEN)-m_DisplayMode.iHeight)/2
				, m_DisplayMode.iWidth+Xplus, m_DisplayMode.iHeight+Yplus, SWP_SHOWWINDOW);


	m_pGSystem->GetGControlSys()->GetDevice()->SetRenderState( D3DRS_AMBIENT, 0xAAAAAA );

	m_pGSystem->GetGControlSys()->SetTextureAutoCompress( true );
	DLogEnable(true);

	// 우선 모든 Layer 들을 생성한다.
	CResourceSysWin32Imp *pResourceSys = (CResourceSysWin32Imp *)m_pGSystem->GetResourceSys();
	pResourceSys->CreateLayerAll();
	pResourceSys->CreateTask(FACTORY_ID_TASK_FRAME_PLAYER);

	CFrameTask *pTask = (CFrameTask *)pResourceSys->GetTask(FACTORY_ID_TASK_FRAME_PLAYER);
	m_pGSystem->GetTaskSys()->PostTaskCommand(CTaskCommand::FRAMESYNC_PUSH_BACK, pTask);
	pWindowSysWin32Imp->SetWndProcTask(pTask);


	// insert only game layer to task.
	CQuickConnection::Instance.Initial();

	// 욕설 필터링을 작동한다.
	LoadCurses("curse.pak");

	// 2006.4.23 doo 메크로채팅 텍스트를 로드한다.
	g_pMacroChatFinder = new CMacroChat;
	g_pMacroChatFinder->Init();
	
	// Login Server 의 ip, port 를 저장한다.
	// 임시로 CQuickConnection 에서 ip, port 를 가져오도록 하였다.
	CInfoSys *pInfoSys = m_pGSystem->GetInfoSys();
	pInfoSys->SetLoginServerAddress((LPCTSTR)CQuickConnection::Instance.m_sServerAddr, CQuickConnection::Instance.m_iServerPort);	
	
	//m_pGSystem->GetInfoSys()->SetPPLName(SName("ppl_ting"));

	// Reject Popup
	CInfoSys::SGameIDInfo *pGameIDInfo;
	pGameIDInfo = m_pGSystem->GetInfoSys()->GetGameIDInfo();
	pGameIDInfo->bRejectPopup = false;
	pGameIDInfo->bObserverChar = false;

	CQuickConnection::Instance.m_nIsQuickMode = 1;
	CQuickConnection::Instance.m_nIsHost = 1;
	CQuickConnection::Instance.m_sServerAddr = "127.0.0.1";
	CQuickConnection::Instance.m_iServerPort = 10000;
	CQuickConnection::Instance.m_nIsFullCourt = 0;
	CQuickConnection::Instance.m_nFrameSpeedOn = 1;
	CQuickConnection::Instance.m_nHostPort = 10001;
	CQuickConnection::Instance.m_nPlayerOn = 1;
	CQuickConnection::Instance.m_sPlayMode = "auto";
	CQuickConnection::Instance.m_vecPos[0] = SVector(1,0,0);
	CQuickConnection::Instance.m_vecPos[1] = SVector(0,0,1);
	CQuickConnection::Instance.m_vecPos[2] = SVector(2,0,0);
	CQuickConnection::Instance.m_vecPos[3] = SVector(0,0,2);
	CQuickConnection::Instance.m_vecPos[4] = SVector(3,0,0);
	CQuickConnection::Instance.m_vecPos[5] = SVector(0,0,3);

	CQuickConnection::Instance.m_sConnectAddr = "127.0.0.1";
	CQuickConnection::Instance.m_sConnectionId = "c1test45";
	CQuickConnection::Instance.m_nClientPort = 10000;
	CQuickConnection::Instance.m_nCharID = 5;
	CQuickConnection::Instance.m_nCharType = 5;
	CQuickConnection::Instance.m_dwTeamID = 0;
	//CQuickConnection::Instance.m_dwMyId = 1;

	if( CQuickConnection::Instance.m_nIsQuickMode )
	{
		CFrameTask* pFrameTask = (CFrameTask*)pTask;
		// game render layer.
		CRenderLayer_Game* pRenderLayer = (CRenderLayer_Game *)pResourceSys->GetRenderLayer( FACTORY_ID_RENDERLAYER_GAME );
		pFrameTask->PostRenderLayerCommand( CRenderLayerCommand::PUSH_BACK, pRenderLayer );
		pRenderLayer->ResourceLoad(m_pGSystem, NULL);

		// game logic layer.
		CLogicLayer* pLogicLayer = pResourceSys->GetLogicLayer( FACTORY_ID_LOGICLAYER_GAME );
		pFrameTask->PostLogicLayerCommand( CLogicLayerCommand::PUSH_BACK, pLogicLayer );

		// host logic layer.
		if( CQuickConnection::Instance.m_nIsHost )
		{
			pLogicLayer = pResourceSys->GetLogicLayer( FACTORY_ID_LOGICLAYER_HOST );
			CLogicLayer_Host* pHostLogicLayer = (CLogicLayer_Host*)pLogicLayer;
			pHostLogicLayer->InitHost(CQuickConnection::Instance.m_nHostPort, 1 );
			pFrameTask->PostLogicLayerCommand( CLogicLayerCommand::PUSH_BACK, pLogicLayer );
		}
		
		m_pGSystem->GetInfoSys()->LoadGameOption("game.cfg");
		
	}
	else // insert all layer to excute game.
	{
		// lobby layer.
//		CInterfaceLayer *pInterfaceLayer_Login = pResourceSys->GetInterfaceLayer(FACTORY_ID_INTERFACELAYER_CREATECHAR);
//		pTask->PostInterfaceLayerCommand(CInterfaceLayerCommand::PUSH_BACK, pInterfaceLayer_Login);
		
		// room layer.
	}

	// plasma 2005.07.06 - Resource Table
#ifdef _DEBUG
/*	CTableResource* pItemRsc = new CTableResource;
	std::vector<std::string> ItemCustomKey;
	ItemCustomKey.push_back("ItemCode");
	pItemRsc->SetCustomKey(ItemCustomKey);
	pItemRsc->Load("text_data/ItemShop.txt");
	CTableRscManager::Instance().AddTableResource( "item", pItemRsc );
		
	CTableResource* pSkillRsc = new CTableResource;
	std::vector<std::string> SkillCustomKey;
	SkillCustomKey.push_back("SkillNo");
	SkillCustomKey.push_back("Kind");
	pSkillRsc->SetCustomKey(SkillCustomKey);
	pSkillRsc->Load("text_data/skillshop.txt");
	CTableRscManager::Instance().AddTableResource( "skill", pSkillRsc );

	CTableResource* pTrainingRsc = new CTableResource;
	std::vector<std::string> TrainingCustomKey;
	TrainingCustomKey.push_back("TrainingNo");
	pTrainingRsc->SetCustomKey(TrainingCustomKey);
	pTrainingRsc->Load("text_data/TrainingShop.txt");
	CTableRscManager::Instance().AddTableResource( "training", pTrainingRsc );
*/
	CTableResource* pItemRsc = new CTableResource;
	std::vector<std::string> ItemCustomKey;
	ItemCustomKey.push_back("ItemCode");
	pItemRsc->SetCustomKey(ItemCustomKey);
	pItemRsc->LoadPack("text_data", "ItemShop.txt");
	CTableRscManager::Instance().AddTableResource( "item", pItemRsc );
		
	CTableResource* pSkillRsc = new CTableResource;
	std::vector<std::string> SkillCustomKey;
	SkillCustomKey.push_back("SkillNo");
	SkillCustomKey.push_back("Kind");
	pSkillRsc->SetCustomKey(SkillCustomKey);
	pSkillRsc->LoadPack("text_data", "skillshop.txt");
	CTableRscManager::Instance().AddTableResource( "skill", pSkillRsc );

	CTableResource* pTrainingRsc = new CTableResource;
	std::vector<std::string> TrainingCustomKey;
	TrainingCustomKey.push_back("TrainingNo");
	pTrainingRsc->SetCustomKey(TrainingCustomKey);
	pTrainingRsc->LoadPack("text_data", "TrainingShop.txt");
	CTableRscManager::Instance().AddTableResource( "training", pTrainingRsc );

#else
	CTableResource* pItemRsc = new CTableResource;
	std::vector<std::string> ItemCustomKey;
	ItemCustomKey.push_back("ItemCode");
	pItemRsc->SetCustomKey(ItemCustomKey);
	pItemRsc->LoadPack("text_data", "ItemShop.txt");
	CTableRscManager::Instance().AddTableResource( "item", pItemRsc );
		
	CTableResource* pSkillRsc = new CTableResource;
	std::vector<std::string> SkillCustomKey;
	SkillCustomKey.push_back("SkillNo");
	SkillCustomKey.push_back("Kind");
	pSkillRsc->SetCustomKey(SkillCustomKey);
	pSkillRsc->LoadPack("text_data", "skillshop.txt");
	CTableRscManager::Instance().AddTableResource( "skill", pSkillRsc );

	CTableResource* pTrainingRsc = new CTableResource;
	std::vector<std::string> TrainingCustomKey;
	TrainingCustomKey.push_back("TrainingNo");
	pTrainingRsc->SetCustomKey(TrainingCustomKey);
	pTrainingRsc->LoadPack("text_data", "TrainingShop.txt");
	CTableRscManager::Instance().AddTableResource( "training", pTrainingRsc );
#endif

	return true;
}