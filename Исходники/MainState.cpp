void MainState::Update() {
	// Moves the player in the specified direction
	if (m_PlayerDirState[kPlayerDirLeft]) {
		m_Player->TranslateBy(Vec2(-5.0, 0.0));
	}
	else if (m_PlayerDirState[kPlayerDirRight]) {
		m_Player->TranslateBy(Vec2(5.0, 0.0));
	}
	else if (m_PlayerDirState[kPlayerDirUp]) {
		m_Player->TranslateBy(Vec2(0.0, -5.0));
	}
	else if (m_PlayerDirState[kPlayerDirDown]) {
		m_Player->TranslateBy(Vec2(0.0, 5.0));
	}

	for (int i = 0; i < m_ProjectileArray.GetSize(); ++i) {
		Rect screenRect = m_EnginePtr->GetScene()->GetScreenRect();

		Projectile* projectile = m_ProjectileArray[i];

		Vec2 pos = projectile->GetWorldPosition();

		if (pos.GetX() < screenRect.GetX() ||
			pos.GetX() > (screenRect.GetX() + screenRect.GetW()) ||
			pos.GetY() < screenRect.GetY() ||
			pos.GetY() > (screenRect.GetY() + screenRect.GetH())) {

			LOG_PRINT("removed");
		}
	}
}