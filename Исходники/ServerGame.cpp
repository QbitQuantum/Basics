/*static unsigned int WINAPI NetworkThread( void * param )
{
	while(1)
	{
	::Sleep(1);
	gServerLogic.net_->Update();
	}
}*/
void PlayGameServer()
{
  r3d_assert(gServerLogic.ginfo_.IsValid());
  switch(gServerLogic.ginfo_.mapId) 
  {
    default: 
      r3dError("invalid map id\n");
      break;
    case GBGameInfo::MAPID_Editor_Particles: 
      r3dGameLevel::SetHomeDir("WorkInProgress\\Editor_Particles"); 
      break;
    case GBGameInfo::MAPID_ServerTest:
      r3dGameLevel::SetHomeDir("WorkInProgress\\ServerTest");
      break;
    case GBGameInfo::MAPID_WZ_Colorado:
      r3dGameLevel::SetHomeDir("WZ_Colorado");
      break;
	case GBGameInfo::MAPID_UB_Cliffside:
      r3dGameLevel::SetHomeDir("WZ_Cliffside");
      break;
    case GBGameInfo::MAPID_UB_CaliWood:
      r3dGameLevel::SetHomeDir("CaliWood");
      break;
    case GBGameInfo::MAPID_UB_Valley:
      r3dGameLevel::SetHomeDir("UB_Valley");
      break;
    case GBGameInfo::MAPID_UB_Area51:
      r3dGameLevel::SetHomeDir("UB_Deserto");
      break;
	case GBGameInfo::MAPID_UB_CryZ:
      r3dGameLevel::SetHomeDir("UB_CryZ");
      break;
  	case GBGameInfo::MAPID_UB_Terra:
      r3dGameLevel::SetHomeDir("UB_Terra");
      break;
  	case GBGameInfo::MAPID_UB_Mega:
      r3dGameLevel::SetHomeDir("UB_Mega");
      break;
  }

  r3dResetFrameTime();
  
  GameWorld_Create();

  u_srand(timeGetTime());
  GameWorld().Init(OBJECTMANAGER_MAXOBJECTS, OBJECTMANAGER_MAXSTATICOBJECTS);
  ServerDummyWorld.Init(OBJECTMANAGER_MAXOBJECTS, OBJECTMANAGER_MAXSTATICOBJECTS);
  
  g_pPhysicsWorld = new PhysXWorld;
  g_pPhysicsWorld->Init();

  r3dTerrain::SetNeedShaders( false );
  LoadLevel_Objects( 1.f );

  gCollectionsManager.Init( 0, 1 );

  r3dOutToLog( "NavMesh.Load...\n" );
  gAutodeskNavMesh.Init();

  r3dResetFrameTime();
  GameWorld().Update();
  ServerDummyWorld.Update();

  r3dGameLevel::SetStartGameTime(r3dGetTime());
  
  r3dOutToLog("server main loop started\n");
  r3dResetFrameTime();
  gServerLogic.OnGameStart();
  
  gKeepAliveReporter.SetStarted(true);
  
 // _beginthreadex ( NULL, 0, NetworkThread, NULL, 0, NULL );
  while(1) 
  {
    ::Sleep(20);		// limit to 100 FPS

	char text[64] ={0};
	sprintf(text,"WarZ Game Server [Running..] id:%d curPeer:%d players:%d/%d",gServerLogic.ginfo_.gameServerId,gServerLogic.curPeersConnected,gServerLogic.curPlayers_,gServerLogic.ginfo_.maxPlayers);
	SetConsoleTitle(text);

	gServerLogic.net_->Update();

    r3dEndFrame();
    r3dStartFrame();
    
    //if(GetAsyncKeyState(VK_F1)&0x8000) r3dError("r3dError test");
    //if(GetAsyncKeyState(VK_F2)&0x8000) r3d_assert(false && "r3d_Assert test");
    gKeepAliveReporter.Tick(gServerLogic.curPlayers_);

    gServerLogic.Tick();
	gServerLogic.UpdateNetId();
    gMasterServerLogic.Tick();
    
    if(gMasterServerLogic.IsMasterDisconnected()) {
      r3dOutToLog("Master Server disconnected, exiting\n");
      gKeepAliveReporter.SetStarted(false);
      return;
    }

    GameWorld().StartFrame();
    GameWorld().Update();
    // fire few ticks of temporary world update, just for safety (physics init and stuff)
    static int TempWorldUpdateN = 0;
    if(TempWorldUpdateN < 20) {
      TempWorldUpdateN++;
      ServerDummyWorld.Update();
    }

    // start physics after game world update right now, as gameworld will move some objects around if necessary
    g_pPhysicsWorld->StartSimulation();
    g_pPhysicsWorld->EndSimulation();

#if ENABLE_AUTODESK_NAVIGATION
    const float t1 = r3dGetTime();
    gAutodeskNavMesh.Update();
    const float t2 = r3dGetTime() - t1;

    bool showSpd = (GetAsyncKeyState('Q') & 0x8000) && (GetAsyncKeyState('E') & 0x8000);
    bool showKys = false; //(GetAsyncKeyState('Q') & 0x8000) && (GetAsyncKeyState('R') & 0x8000);

    extern int _zstat_NumZombies;
    extern int _zstat_NavFails;
    extern int _zstat_Disabled;
    if(showKys) {
      gAutodeskNavMesh.perfBridge.Dump();
      r3dOutToLog("NavMeshUpdate %f sec, z:%d, bad:%d, f:%d\n", t2, _zstat_NumZombies, _zstat_Disabled, _zstat_NavFails);
    }
    if(showSpd) {
      r3dOutToLog("NavMeshUpdate %f sec, z:%d, bad:%d, f:%d\n", t2, _zstat_NumZombies, _zstat_Disabled, _zstat_NavFails);
    }
#ifndef _DEBUG    
    if((t2 > (1.0f / 60.0f))) {
      r3dOutToLog("!!!! NavMeshUpdate %f sec, z:%d, bad:%d, f:%d\n", t2, _zstat_NumZombies, _zstat_Disabled, _zstat_NavFails);
      //gAutodeskNavMesh.perfBridge.Dump();
      //r3dOutToLog("!!!! NavMeshUpdate %f sec, z:%d, bad:%d, f:%d, navPend:%d\n", t2, _zstat_NumZombies, _zstat_Disabled, _zstat_NavFails, _zstat_UnderProcess);
    }
#endif
#endif // ENABLE_AUTODESK_NAVIGATION

    GameWorld().EndFrame();
    
    if(gServerLogic.gameFinished_)
      break;
  }

  // set that we're finished
  gKeepAliveReporter.SetStarted(false);

  gMasterServerLogic.FinishGame();
  
  gServerLogic.DumpPacketStatistics();
  
  gCollectionsManager.Destroy();

  GameWorld_Destroy();
  ServerDummyWorld.Destroy();
  
  return;
}