void GameManager::ProcessState()
{
	switch (m_player->GetState())
	{
	case ENTER_BABE: // Enter -> In
	{
		m_babeBg->setOpacity(105);
		m_babe->SetState(CONTROLED);
		m_player->EnterEvent(m_babe->getPosition());
	}
		break;
	case IN_BABE: // In -> Exit
	{
		Vec2 playerPos = m_player->getPosition();
		Vec2 babePos = m_babe->getPosition();
		Vec2 deltaPos = (playerPos - babePos) / 20;
		if (babePos.distance(playerPos) > 100)
		{
			m_babe->setPosition(babePos + deltaPos);
		}
		
	}
		break;
	case EXIT_BABE: // Exit -> Out
	{
		m_babeBg->setOpacity(0);
		m_babe->SetState(WALKAROUND);
		m_player->ExitEvent();
	}
	break;
	case OUT_BABE: // Out -> Enter
	{

	}
	}
}