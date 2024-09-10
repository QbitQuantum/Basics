void ZGameInput::Update(float fElapsed)
{
	/*
	{
		static DWORD dwLastTime = timeGetTime();

		if(timeGetTime()-dwLastTime > 10 )
		{
			dwLastTime = timeGetTime();
			{
				MTextArea *pTextArea = (MTextArea*)ZGetGameInterface()->GetIDLResource()->FindWidget("CombatChatOutputTest");
				if(pTextArea)
				{
					char szbuffer[256];
					for(int i=0;i<100;i++)
					{
						szbuffer[i]=rand()%255+1;
					}
					szbuffer[100]=0;
					pTextArea->AddText(szbuffer);
					if(pTextArea->GetLineCount()>10) pTextArea->DeleteFirstLine();
				}

			}

			{
				MTextArea *pTextArea = (MTextArea*)ZGetGameInterface()->GetIDLResource()->FindWidget("CombatChatOutput");
				if(pTextArea)
				{
					char szbuffer[256];
					for(int i=0;i<100;i++)
					{
						szbuffer[i]=rand()%255+1;
					}
					szbuffer[100]=0;
					pTextArea->AddText(szbuffer);
					if(pTextArea->GetLineCount()>10) pTextArea->DeleteFirstLine();
				}
			}
		}
	}//*/

//	if(RIsActive() && !g_pGame->IsReplay())

	//jintriple3 메모리 프록시...비트 패킹..
	const ZCharaterStatusBitPacking &uStatus = ZGetGame()->m_pMyCharacter->m_dwStatusBitPackingValue.Ref();
	ZMyCharaterStatusBitPacking & zStatus = ZGetGame()->m_pMyCharacter->m_statusFlags.Ref();


	if(RIsActive())
	{
		ZCamera* pCamera = ZGetGameInterface()->GetCamera();
		ZMyCharacter* pMyCharacter = ZGetGame()->m_pMyCharacter;
		if ((!pMyCharacter) || (!pMyCharacter->GetInitialized())) return;

		// 커서가 없는 상태에서만 카메라및 게임입력을 받는다
		if(!ZGetGameInterface()->IsCursorEnable())
		{
			{
				float fRotateX = 0;
				float fRotateY = 0;

#ifdef _DONOTUSE_DINPUT_MOUSE
				// DINPUT 을 사용하지 않는경우
				int iDeltaX, iDeltaY;

				POINT pt;
				GetCursorPos(&pt);
				ScreenToClient(g_hWnd,&pt);
				iDeltaX = pt.x-RGetScreenWidth()/2;
				iDeltaY = pt.y-RGetScreenHeight()/2;

				float fRotateStep = 0.0005f * Z_MOUSE_SENSITIVITY*10.0f;
				fRotateX = (iDeltaX * fRotateStep);
				fRotateY = (iDeltaY * fRotateStep);

#else
				// 마우스 입력 dinput 처리

				ZGetInput()->GetRotation(&fRotateX,&fRotateY);
#endif

				bool bRotateEnable=false;
				// TODO : 칼로 벽에 꽂았을때 프리카메라로 바꾸자
				if( !zStatus.m_bSkill && !uStatus.m_bWallJump && !uStatus.m_bWallJump2 && !zStatus.m_bWallHang && 
					!uStatus.m_bTumble && !uStatus.m_bBlast && !uStatus.m_bBlastStand && !uStatus.m_bBlastDrop )
					bRotateEnable=true;
				if (pMyCharacter->IsDie()) bRotateEnable = true;

				if (RIsActive())
				{
					ZCamera *pCamera = ZGetGameInterface()->GetCamera();

					pCamera->m_fAngleX += fRotateY;
					pCamera->m_fAngleZ += fRotateX;

					if(pCamera->GetLookMode()==ZCAMERA_MINIMAP) {
						pCamera->m_fAngleX=max(pi/2+.1f,pCamera->m_fAngleX);
						pCamera->m_fAngleX=min(pi-0.1f,pCamera->m_fAngleX);
					}else {
						static float lastanglex,lastanglez;
						if(bRotateEnable)
						{
							// 정밀도 유지를 위해 0~2pi 로 유지
							pCamera->m_fAngleZ = fmod(pCamera->m_fAngleZ,2*PI);
							pCamera->m_fAngleX = fmod(pCamera->m_fAngleX,2*PI);

							pCamera->m_fAngleX=max(CAMERA_ANGLEX_MIN,pCamera->m_fAngleX);
							pCamera->m_fAngleX=min(CAMERA_ANGLEX_MAX,pCamera->m_fAngleX);

							lastanglex=pCamera->m_fAngleX;
							lastanglez=pCamera->m_fAngleZ;
						}else
						{
							// 각도제한이 필요하다
							pCamera->m_fAngleX=max(CAMERA_ANGLEX_MIN,pCamera->m_fAngleX);
							pCamera->m_fAngleX=min(CAMERA_ANGLEX_MAX,pCamera->m_fAngleX);

							pCamera->m_fAngleX=max(lastanglex-pi/4.f,pCamera->m_fAngleX);
							pCamera->m_fAngleX=min(lastanglex+pi/4.f,pCamera->m_fAngleX);

							pCamera->m_fAngleZ=max(lastanglez-pi/4.f,pCamera->m_fAngleZ);
							pCamera->m_fAngleZ=min(lastanglez+pi/4.f,pCamera->m_fAngleZ);

						}
					}

					ZCombatInterface* pCombatInterface = ZGetGameInterface()->GetCombatInterface();
					if (pCombatInterface && !pCombatInterface->IsChat() &&
						(pCamera->GetLookMode()==ZCAMERA_FREELOOK || pCamera->GetLookMode()==ZCAMERA_MINIMAP))
					{

						rvector right;
						rvector forward=RCameraDirection;
						CrossProduct(&right,rvector(0,0,1),forward);
						Normalize(right);
						const rvector up = rvector(0,0,1);

						rvector accel = rvector(0,0,0);

						if(ZIsActionKeyPressed(ZACTION_FORWARD)==true)	accel+=forward;
						if(ZIsActionKeyPressed(ZACTION_BACK)==true)		accel-=forward;
						if(ZIsActionKeyPressed(ZACTION_LEFT)==true)		accel-=right;
						if(ZIsActionKeyPressed(ZACTION_RIGHT)==true)	accel+=right;
						if(ZIsActionKeyPressed(ZACTION_JUMP)==true)		accel+=up;
						if(ZIsActionKeyPressed(ZACTION_USE_WEAPON)==true)			accel-=up;

						rvector cameraMove = 
							(pCamera->GetLookMode()==ZCAMERA_FREELOOK ? 1000.f : 10000.f )		// 미니맵모드는 빨리 움직임
							* fElapsed*accel;

						rvector targetPos = pCamera->GetPosition()+cameraMove;

						// 프리룩은 충돌체크를 한다
						if(pCamera->GetLookMode()==ZCAMERA_FREELOOK)
							ZGetGame()->GetWorld()->GetBsp()->CheckWall(pCamera->GetPosition(),targetPos,ZFREEOBSERVER_RADIUS,0.f,RCW_SPHERE);
						else
						// 미니맵은 범위내에 있는지 체크한다
						{
							rboundingbox *pbb = &ZGetGame()->GetWorld()->GetBsp()->GetRootNode()->bbTree;
							targetPos.x = max(min(targetPos.x,pbb->maxx),pbb->minx);
							targetPos.y = max(min(targetPos.y,pbb->maxy),pbb->miny);

							ZMiniMap *pMinimap = ZGetGameInterface()->GetMiniMap();
							if(pMinimap)
								targetPos.z = max(min(targetPos.z,pMinimap->GetHeightMax()),pMinimap->GetHeightMin());
							else
								targetPos.z = max(min(targetPos.z,7000),2000);

							
						}

						pCamera->SetPosition(targetPos);

					}
					else if ( !ZGetGame()->IsReplay())
					{
						pMyCharacter->ProcessInput( fElapsed);
					}
				}
			}
			POINT pt={RGetScreenWidth()/2,RGetScreenHeight()/2};
			ClientToScreen(g_hWnd,&pt);
			SetCursorPos(pt.x,pt.y);

			// 대쉬 키 입력 검사
			GameCheckSequenceKeyCommand();

		}else
			pMyCharacter->ReleaseButtonState();	// 메뉴가 나왔을때는 버튼이 눌리지 않은상태로 돌려놓는다
	}
}