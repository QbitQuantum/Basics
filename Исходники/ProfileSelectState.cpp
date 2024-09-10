void CProfileSelectState::MenuInput()
{
	SGD::InputManager* input = SGD::InputManager::GetInstance();

	if (state == MyState::ConfirmOverwrite)
	{
#if ARCADE
		if (input->IsButtonPressed(0, 1) || input->IsButtonPressed(1, 1))
#else
		if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0, 1))
#endif
		{
			delete confirm;
			confirm = nullptr;
			state = MyState::Menu;
			return;
		}
		switch (confirm->Input())
		{
		case 0:
		{
			delete confirm;
			confirm = nullptr;
			CGameplayState::GetInstance()->DeleteProfile(currentProfile+1);
			profiles[currentProfile] = CreateProfile();
			TutorialConfirmation();
			break;
		}
		case 1:
		{
			delete confirm;
			confirm = nullptr;
			state = MyState::Menu;
		}
		case -1:
		default:
			break;
		}
		return;
	}

	if (state == MyState::ConfirmDelete)
	{
#if ARCADE
		if (input->IsButtonPressed(0, 1) || input->IsButtonPressed(1, 1))
#else
		if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0, 1))
#endif
		{
			delete confirm;
			confirm = nullptr;
			state = MyState::Menu;
			return;
		}
		switch (confirm->Input())
		{
		case 0:
			CGameplayState::GetInstance()->DeleteProfile(currentProfile+1);
			profiles[currentProfile] = CreateProfile();
			//profiles[currentProfile].profile = currentProfile + 1;
			//Don't break! They both delete confirm and change state beck to menu
		case 1:
			delete confirm;
			confirm = nullptr;
			state = MyState::Menu;
			break;
		case -1:
		default:
			break;
		}
		return;
	}

	if (state == MyState::ConfirmTutorial)
	{
#if ARCADE
		if (input->IsButtonPressed(0, 1) || input->IsButtonPressed(1, 1))
#else
		if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0, 1))
#endif
		{
			delete confirm;
			confirm = nullptr;
			state = MyState::Menu;
			return;
		}
		switch (confirm->Input())
		{
		case 0:
			profiles[currentProfile].currLevel = Level::Gen1;
		case 1:
			CGameplayState::GetInstance()->SetSaveData(profiles[currentProfile]);
			Game::GetInstance()->PopState();
			Game::GetInstance()->PopState();
			Game::GetInstance()->PushState(CGameplayState::GetInstance());
			break;
		case 2:
			delete confirm;
			confirm = nullptr;
			state = MyState::Menu;
			break;
		case -1:
		default:
			break;
		}
		return;
	}

#if ARCADE
	if (input->IsButtonPressed(0, 1) || input->IsButtonPressed(1, 1))
#else
	if (input->IsKeyPressed(SGD::Key::Escape) || input->IsButtonPressed(0, 1))
#endif
	{
		state = MyState::Idle;
		return;
	}

	switch (menu->Input())
	{
	case 0:
		if (profiles[currentProfile].currLevel == Level::Tutorial)
		{
			TutorialConfirmation();
			break;
		}
		CGameplayState::GetInstance()->SetSaveData(profiles[currentProfile]);
		Game::GetInstance()->PopState();
		Game::GetInstance()->PopState();
		Game::GetInstance()->PushState(CGameplayState::GetInstance());
		break;
	case 1:
	{
		std::vector<std::string> yesno;
		yesno.push_back("Yes");
		yesno.push_back("No");
		confirm = new CMenu(&Game::GetInstance()->FontPoiret, yesno, "Overwrite?", { Game::GetInstance()->GetScreenWidth() * .55f, Game::GetInstance()->GetScreenHeight() * .6f }, false);
		state = MyState::ConfirmOverwrite;
		break;
	}
	case 2:
	{
		std::vector<std::string> yesno;
		yesno.push_back("Yes");
		yesno.push_back("No");
		confirm = new CMenu(&Game::GetInstance()->FontPoiret, yesno, "Delete?", { Game::GetInstance()->GetScreenWidth() * .55f, Game::GetInstance()->GetScreenHeight() * .6f }, false);
		state = MyState::ConfirmDelete;
		break;
	}
	case 3:
	{
		state = MyState::Idle;
		break;
	}
	case 4:
	{
		Game::GetInstance()->PopState();
		//Game::GetInstance()->PushState(CMainMenuState::GetInstance());
		break;
	}
	case -1:
	default:
		break;
	}
}