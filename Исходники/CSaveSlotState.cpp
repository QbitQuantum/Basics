bool CSaveSlotState::Input(void)
{
	CGame* pGame = CGame::GetInstance();
	CSGD_DirectInput* pDI = CSGD_DirectInput::GetInstance();
	CGamePlayState* pGamePlay = CGamePlayState::GetInstance();
	CSGD_FModManager* FM = CSGD_FModManager::GetInstance();
	//Enter
	if(pDI->KeyPressed(DIK_RETURN) ||
		pDI->JoystickButtonPressed(0))
	{
		switch(m_nIndex)
		{
		case SELECT:
			{
				//Change to GamePlayState
				FM->StopSound( CMainMenuState::GetInstance()->GetSongID() );
				pGame->ChangeState(pGamePlay);
				break;
			}
		case SLOTDELETE:
			{
				Delete();
				break;
			}
		case BACK:
			{
				pGame->ChangeState(CMainMenuState::GetInstance());
				break;
			}
		};
	}

	//Directional
	//Up
	if(pDI->KeyPressed(DIK_UP) ||
	   pDI->JoystickGetLStickDirPressed(DIR_UP, 0))
	{
		FM->PlaySoundA(m_nSoundID);
		if(m_nIndex != 0)
			m_nIndex -= 1;
		else
			m_nIndex = NUMSLOTOPTIONS - 1;
	}
	//Down
	if(pDI->KeyPressed(DIK_DOWN) ||
		pDI->JoystickGetLStickDirPressed(DIR_DOWN, 0))
	{
		FM->PlaySoundA(m_nSoundID);
		if(m_nIndex != (NUMSLOTOPTIONS - 1))
			m_nIndex += 1;
		else
			m_nIndex = 0;
	}
	//Left
	if(pDI->KeyPressed(DIK_LEFT) ||
		pDI->JoystickGetLStickDirPressed(DIR_LEFT, 0))
	{
		SetSaveSlot(--m_nCurrSaveSlot);
		FM->PlaySoundA(m_nSoundID);
	}
	//Right
	if(pDI->KeyPressed(DIK_RIGHT) ||
		pDI->JoystickGetLStickDirPressed(DIR_RIGHT, 0))
	{
		SetSaveSlot(++m_nCurrSaveSlot);
		FM->PlaySoundA(m_nSoundID);
	}
	
	return true;
}