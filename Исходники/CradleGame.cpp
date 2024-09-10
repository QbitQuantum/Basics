int CradleGame::BaseUpdate()
{
	m_timer->Update();

	if (m_cInput)
		m_cInput->Update();

	m_total += m_timer->GetDelta();
	m_fps++;

	if (m_total > 1.0f)
	{
		m_total -= 1.0f;
		wprintf_s(L"FPS: %d\n", m_fps);
	
		m_fps = 0;
	}


	// PrePhysicsUpdate();
	Update();
	// PostPhysicsUpdate();

	Render();

	return 0;
}