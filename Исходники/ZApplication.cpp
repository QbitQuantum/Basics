bool ZApplication::OnCreate(ZLoadingProgress *pLoadingProgress)
{	
	string strFileNameZItem(FILENAME_ZITEM_DESC);
	string strFileNameZItemLocale(FILENAME_ZITEM_DESC_LOCALE);
	string strFileNameZBuff(FILENAME_BUFF_DESC);
	string strFileNameWorlditem(FILENAME_WORLDITEM);
	string strFileNameAbuse(FILENAME_ABUSE);

// #ifndef _DEBUG
// 	strFileNameZItem += ".mef";
// 	strFileNameZItemLocale += ".mef";
// 	strFileNameZBuff += ".mef";
// 	strFileNameWorlditem += ".mef";
// 	strFileNameAbuse += ".mef";
// #endif

	MInitProfile();

	// 멀티미디어 타이머 초기화
	TIMECAPS tc;

	mlog("ZApplication::OnCreate : begin\n");

	//ZGetSoundEngine()->Enumerate();
	//for( int i = 0 ; i < ZGetSoundEngine()->GetEnumDeviceCount() ; ++i)
	//{
	//	sprintf(szDesc, "Sound Device %d = %s\n", i, ZGetSoundEngine()->GetDeviceDescription( i ) );
	//	mlog(szDesc);
	//}

	__BP(2000,"ZApplication::OnCreate");

#define MMTIMER_RESOLUTION	1
	if (TIMERR_NOERROR == timeGetDevCaps(&tc,sizeof(TIMECAPS)))
	{
		m_nTimerRes = min(max(tc.wPeriodMin,MMTIMER_RESOLUTION),tc.wPeriodMax);
		timeBeginPeriod(m_nTimerRes);
	}

	// 한국도 서버리스트 선택 과정이 추가된다.
	// IP가 없으면 로그인화면으로 이동, IP가 있으면 바로 캐릭터 선택창으로 이동
	if (ZApplication::GetInstance()->GetLaunchMode() == ZApplication::ZLAUNCH_MODE_NETMARBLE)
		m_nInitialState = GUNZ_DIRECTLOGIN;

	if (ZGameInterface::m_sbRemainClientConnectionForResetApp == true)
		m_nInitialState = GUNZ_LOBBY;	// if during reload client for changing language, pass login step.

	DWORD _begin_time,_end_time;
#define BEGIN_ { _begin_time = timeGetTime(); }
#define END_(x) { _end_time = timeGetTime(); float f_time = (_end_time - _begin_time) / 1000.f; mlog("\n-------------------> %s : %f \n\n", x,f_time ); }

	__BP(2001,"m_SoundEngine.Create");

	ZLoadingProgress soundLoading("Sound",pLoadingProgress,.12f);
	BEGIN_;
#ifdef _BIRDSOUND
	m_SoundEngine.Create(RealSpace2::g_hWnd, 44100, Z_AUDIO_HWMIXING, GetFileSystem());
#else
	m_SoundEngine.Create(RealSpace2::g_hWnd, Z_AUDIO_HWMIXING, &soundLoading );
#endif
	END_("Sound Engine Create");
	soundLoading.UpdateAndDraw(1.f);

	__EP(2001);

	// mlog("ZApplication::OnCreate : m_SoundEngine.Create\n");
	mlog( "sound engine create.\n" );

//	ZGetInitialLoading()->SetPercentage( 15.0f );
//	ZGetInitialLoading()->Draw( MODE_DEFAULT, 0 , true );

//	loadingProgress.UpdateAndDraw(.3f);

	RegisterForbidKey();

	__BP(2002,"m_pInterface->OnCreate()");

	ZLoadingProgress giLoading("GameInterface",pLoadingProgress,.35f);

	BEGIN_;
	m_pGameInterface=new ZGameInterface("GameInterface",Mint::GetInstance()->GetMainFrame(),Mint::GetInstance()->GetMainFrame());
	m_pGameInterface->m_nInitialState = m_nInitialState;
	if(!m_pGameInterface->OnCreate(&giLoading))
	{
		mlog("Failed: ZGameInterface OnCreate\n");
		SAFE_DELETE(m_pGameInterface);
		return false;
	}

	// mlog("Bird : 5\n");

	m_pGameInterface->SetBounds(0,0,MGetWorkspaceWidth(),MGetWorkspaceHeight());
	END_("GameInterface Create");

	giLoading.UpdateAndDraw(1.f);

	m_pStageInterface = new ZStageInterface();
	m_pOptionInterface = new ZOptionInterface;

	__EP(2002);

#ifdef _BIRDTEST
	goto BirdGo;
#endif

//	ZGetInitialLoading()->SetPercentage( 30.0f );
//	ZGetInitialLoading()->Draw( MODE_DEFAULT, 0 , true );
//	loadingProgress.UpdateAndDraw(.7f);

	__BP(2003,"Character Loading");

	ZLoadingProgress meshLoading("Mesh",pLoadingProgress,.41f);
	BEGIN_;
	// zip filesystem 을 사용하기 때문에 꼭 ZGameInterface 다음에 사용한다...
//	if(m_MeshMgr.LoadXmlList("model/character_lobby.xml")==-1) return false;
	if(m_MeshMgr.LoadXmlList("model/character.xml",ZProgressCallBack,&meshLoading)==-1)	
		return false;

	mlog( "Load character.xml success,\n" );

	END_("Character Loading");
	meshLoading.UpdateAndDraw(1.f);

//	ZLoadingProgress npcLoading("NPC",pLoadingProgress,.1f);
#ifdef _QUEST
	//if(m_NPCMeshMgr.LoadXmlList("model/npc.xml",ZProgressCallBack,&npcLoading) == -1)
	if(m_NPCMeshMgr.LoadXmlList("model/npc.xml") == -1)
		return false;
#endif

	__EP(2003);

	// 모션에 연결된 사운드 파일중 없는것을 제거한다.. 
	// 엔진에서는 사운드에 접근할수없어서.. 
	// 파일체크는 부담이크고~

	CheckSound();

//	npcLoading.UpdateAndDraw(1.f);
	__BP(2004,"WeaponMesh Loading");

	BEGIN_;

	string strFileNameWeapon("model/weapon.xml");
// #ifndef _DEBUG
// 	strFileNameWeapon += ".mef";
// #endif
	if(m_WeaponMeshMgr.LoadXmlList((char*)strFileNameWeapon.c_str())==-1) 
		return false;

	END_("WeaponMesh Loading");

	__EP(2004);

	__BP(2005,"Worlditem Loading");

	ZLoadingProgress etcLoading("etc",pLoadingProgress,.02f);
	BEGIN_;

#ifdef	_WORLD_ITEM_
	m_MeshMgr.LoadXmlList((char*)strFileNameWorlditem.c_str());
#endif

	mlog("Load weapon.xml success. \n");

//*/
	END_("Worlditem Loading");
	__EP(2005);


#ifdef _BIRDTEST
BirdGo:
#endif

	__BP(2006,"ETC .. XML");

	BEGIN_;
	CreateConsole(ZGetGameClient()->GetCommandManager());

	// mlog("ZApplication::OnCreate : CreateConsole \n");

	m_pLogFrame = new MCommandLogFrame("Command Log", Mint::GetInstance()->GetMainFrame(), Mint::GetInstance()->GetMainFrame());
	int nHeight = MGetWorkspaceHeight()/3;
	m_pLogFrame->SetBounds(0, MGetWorkspaceHeight()-nHeight-1, MGetWorkspaceWidth()-1, nHeight);
	m_pLogFrame->Show(false);

	m_pGameInterface->SetFocusEnable(true);
	m_pGameInterface->SetFocus();
	m_pGameInterface->Show(true);


	if (!MGetMatchItemDescMgr()->ReadCache())
	{
		if (!MGetMatchItemDescMgr()->ReadXml(GetFileSystem(), strFileNameZItem.c_str()))
		{
			MLog("Error while Read Item Descriptor %s\n", strFileNameZItem.c_str());
		}
		if (!MGetMatchItemDescMgr()->ReadXml(GetFileSystem(), strFileNameZItemLocale.c_str()))
		{
			MLog("Error while Read Item Descriptor %s\n", strFileNameZItemLocale.c_str());
		}

		MGetMatchItemDescMgr()->WriteCache();
	}
	mlog("Load zitem info success.\n");

	if( !MGetMatchBuffDescMgr()->ReadXml(GetFileSystem(), strFileNameZBuff.c_str()) )
	{
		MLog("Error while Read Buff Descriptor %s\n", strFileNameZBuff.c_str());
	}
	mlog("Load zBuff info success.\n");


//	if (!MGetMatchItemEffectDescMgr()->ReadXml(GetFileSystem(), FILENAME_ZITEMEFFECT_DESC))
//	{
//		MLog("Error while Read Item Descriptor %s\n", FILENAME_ZITEMEFFECT_DESC);
//	}
//	mlog("Init effect manager success.\n");

	if (!MGetMatchWorldItemDescMgr()->ReadXml(GetFileSystem(), strFileNameWorlditem.c_str() ))
	{
		MLog("Error while Read Item Descriptor %s\n", strFileNameWorlditem.c_str());
	}
	mlog("Init world item manager success.\n");

	
	if (!MGetMapDescMgr()->Initialize(GetFileSystem(), "system/map.xml"))
	{
		MLog("Error while Read map Descriptor %s\n", "system/map.xml");
	}
	mlog("Init map Descriptor success.\n");


	string strFileChannelRule("system/channelrule.xml");
// #ifndef _DEBUG
// 	strFileChannelRule += ".mef";
// #endif
	if (!ZGetChannelRuleMgr()->ReadXml(GetFileSystem(), strFileChannelRule.c_str()))
	{
		MLog("Error while Read Item Descriptor %s\n", strFileChannelRule.c_str());
	}
	mlog("Init channel rule manager success.\n");
/*
	if (!MGetNPCGroupMgr()->ReadXml(GetFileSystem(), "system/monstergroup.xml"))
	{
		MLog("Error while Read Item Descriptor %s", "system/monstergroup.xml");
	}
	mlog("ZApplication::OnCreate : ZGetNPCGroupMgr()->ReadXml \n");
*/
	// if (!MGetChattingFilter()->Create(GetFileSystem(), "system/abuse.xml"))
	bool bSucceedLoadAbuse = MGetChattingFilter()->LoadFromFile(GetFileSystem(), strFileNameAbuse.c_str());
	if (!bSucceedLoadAbuse || MGetChattingFilter()->GetNumAbuseWords() == 0)
	{
		// 해킹으로 abuse-list 파일자체를 없애거나 내용을 비웠을 경우 실행을 멈추게 하자
		MLog("Error while Read Abuse Filter %s\n", strFileNameAbuse.c_str());
		MessageBox(NULL, ZErrStr(MERR_FIND_INVALIDFILE), ZMsg( MSG_WARNING), MB_OK);	// TODO: 풀스크린에서 메시지 박스는 좀 곤란함;
		return false;
	}
	mlog( "Init abuse manager success.\n" );

	


#ifdef _QUEST_ITEM
	if( !GetQuestItemDescMgr().ReadXml(GetFileSystem(), FILENAME_QUESTITEM_DESC) )
	{
		MLog( "Error while read quest tiem descrition xml file.\n" );
	}
#endif

	mlog("Init chatting filter. success\n");

	if(!m_SkillManager.Create()) {
		MLog("Error while create skill manager\n");
	}

	END_("ETC ..");

#ifndef _BIRDTEST
	etcLoading.UpdateAndDraw(1.f);
#endif

	//CoInitialize(NULL);

//	ZGetInitialLoading()->SetPercentage( 40.0f );
//	ZGetInitialLoading()->Draw( MODE_DEFAULT, 0 , true );
//	loadingProgress.UpdateAndDraw(1.f);

	ZGetEmblemInterface()->Create();

	__EP(2006);

	__EP(2000);

	__SAVEPROFILE("profile_loading.txt");

	if (ZCheckFileHack() == true)
	{
		MLog("File Check Failed\n");
		return false;
	}

	ZSetupDataChecker_Global(&m_GlobalDataChecker);


#ifdef LOCALE_NHNUSA
	GetNHNUSAReport().ReportInitComplete();
#endif


	return true;
}