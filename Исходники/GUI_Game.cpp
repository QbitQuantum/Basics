void GameOnSelect( VariantList* pVList )
{
	Entity *pEntClicked = pVList->m_variant[1].GetEntity();

	Tetris* tetris = Tetris::GetInstance();
	Config* config = Config::GetInstance();

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_GAMEPLAY_MENU_BUTTON )
	{
		GetApp()->buttonClickSound();

		if( tetris->isEndGame() )
		{
			SlideScreen( pEntClicked->GetParent(), false );
			GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		
			GetApp()->setGame( false );
			GetApp()->setContinueBtn( false );

			if( tetris->getScoreInt() > config->getMinScore() )
			{
				GameState::SetState( new GS_Menu() );
				InputBestScoreCreate( pEntClicked->GetParent()->GetParent() );
			}
			else
			{
				tetris->ResetEndGame();

				GameState::SetState( new GS_Menu() );
				MainMenuCreate( pEntClicked->GetParent()->GetParent() );
			}
		
			tetris->FreeInstance();
			config->FreeInstance();

			return;
		}

		GameState::SetState( new GS_Menu() );

		if( config->getMusic() )
		{
			GetAudioManager()->StopMusic();
		}
		
		GetApp()->setGame( false );
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		MainMenuCreate( pEntClicked->GetParent()->GetParent() );
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_GAMEPLAY_DOWN && !tetris->isEndGame() )
	{
		if( config->getSoundEffects() )
		{
			GetAudioManager()->Play( GetApp()->getResourceInstance()->getItem(GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_FIGURE_DOWN ) );
		}
		tetris->ClickForceDown();
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_GAMEPLAY_LEFT && !tetris->isEndGame() )
	{
		buttonMoveSound();
		tetris->ClickLeft();
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_GAMEPLAY_RIGHT && !tetris->isEndGame() )
	{
		buttonMoveSound();
		tetris->ClickRight();
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_GAMEPLAY_ROTATE && !tetris->isEndGame() )
	{
		buttonMoveSound();
		tetris->ClickRotate();
	}

	tetris->FreeInstance();
	config->FreeInstance();
}