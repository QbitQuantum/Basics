void WinState::Enter()
{
	//ShowCursor(TRUE);

	this->m_Renderer = m_Game->GetRenderer();
	this->m_Choice = 0;
	this->m_AM = CAssetManager::GetInstance();

	m_bMain = true;
	m_bCredits = false;
	m_bFadeOut = false;

	m_FadeTimer = 1.0f;
	m_Timer = 0.0f;

	m_bSoundMain = true;
	m_bSoundCredits = true;
	m_bSoundCheck = true;
	m_bEsc = false;

	//BLACK BACKGROUND
	Vec4f white = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLint temp;
	temp = CAssetManager::GetInstance()->GetTexture(M_WIN_BACKGROUND);

	m_WinElements[WIN_BLACK_BACKGROUND_ELEMENT].Setup(m_Renderer, CAssetManager::GetInstance()->GetTexture(M_BLACK_BACKGROUND), 
		RECTANGLE(0.0f, (float)m_Game->GetScreenWidth(), 0.0f, float(m_Game->GetScreenHeight())), 0.0f, 0.0f, 0.0f, 720.0f / m_Renderer->GetScreenHeight(), white);
			
	m_WinElements[WIN_BACKGROUND_ELEMENT].Setup(m_Renderer, temp, RECTANGLE(0.0f, 1280.0f, 0.0f, 720.0f),
		(float)m_Renderer->GetScreenWidth() / 2.0f - 640.0f * (m_Renderer->GetScreenWidth() / 1280.0f),
		(float)m_Renderer->GetScreenHeight() / 2.0f - 360.0f * (m_Renderer->GetScreenWidth() / 1280.0f),
		0.0f, (m_Renderer->GetScreenWidth() / 1280.0f) * (720.0f / m_Renderer->GetScreenHeight()), white);

	m_BlackLetterbox.Setup(m_Renderer, CAssetManager::GetInstance()->GetTexture(M_BLACK_BACKGROUND), 
		RECTANGLE(0.0f, (float)m_Game->GetScreenWidth(), 0.0f, (float)m_Game->GetScreenHeight()), 0.0f, 0.0f, 0.0f, 720.0f / m_Renderer->GetScreenHeight(), white);
	
//#if defined(_DEBUG) || defined(_BETA)
//	m_WinElements[WIN_BACKGROUND_ELEMENT].Setup(m_Renderer, CAssetManager::GetInstance()->GetTexture(M_WIN_BACKGROUND_1024x768), 
//		RECTANGLE(0.0f, (float)m_Game->GetScreenWidth(), 0.0f, float(m_Game->GetScreenHeight())), 0.0f, 0.0f, 0.0f, 720.0f / m_Renderer->GetScreenHeight(), white);
//#else
//	m_WinElements[WIN_BACKGROUND_ELEMENT].Setup(m_Renderer, CAssetManager::GetInstance()->GetTexture(M_WIN_BACKGROUND_1280x720), 
//		RECTANGLE(0.0f, (float)m_Game->GetScreenWidth(), 0.0f, float(m_Game->GetScreenHeight())), 0.0f, 0.0f, 0.0f, 720.0f / m_Renderer->GetScreenHeight(), white);
//#endif

	//NON-HIGHLIGHTED BUTTONS --------------------------------------------------------------------------------------------
#pragma region Non-Highlighted Buttons

	//m_WinElements[WIN_MAIN_ELEMENT].Setup(m_Renderer, CAssetManager::GetInstance()->GetTexture(BUTTON_MAINMENU), 
	//	RECTANGLE(0.0f, 256.0f, 0.0f, 64.0f),
	//	(float)(m_Game->GetScreenWidth() /2) - 384 * (m_Renderer->GetScreenHeight() / 720.0f),
	//	((float)m_Game->GetScreenHeight() / 2) +96 * (m_Renderer->GetScreenHeight() / 720.0f),
	//	0.0f, 1.0f, white);

	m_WinElements[WIN_CREDITS_ELEMENT].Setup(m_Renderer, CAssetManager::GetInstance()->GetTexture(BUTTON_CREDITS), 
		RECTANGLE(0.0f, 256.0f, 0.0f, 64.0f),
		(float)(m_Game->GetScreenWidth() /2) - (256.0f * 0.5f) * (m_Renderer->GetScreenHeight() / 720.0f),
		((float)m_Game->GetScreenHeight() / 2) +88 * (m_Renderer->GetScreenHeight() / 720.0f),
		0.0f, 1.0f, white);

	
	m_WinElements[WIN_ALL3_ELEMENT].Setup( m_Renderer, CAssetManager::GetInstance()->GetTexture(MENU_ALL3),
		RECTANGLE(0.0f, 384.0f, 0.0f, 256.0f),
		float((m_Game->GetScreenWidth() / 2) - 440 * (m_Game->GetScreenHeight() / 720.0f)),
		((float)m_Game->GetScreenHeight()) - 180 * (m_Game->GetScreenHeight() / 720.0f),
		0.0f, 0.75f, white );

	m_WinElements[WIN_ALL3_CONTROLLER_ELEMENT].Setup( m_Renderer, CAssetManager::GetInstance()->GetTexture(MENU_ALL3_CONTROLLER),
		RECTANGLE(0.0f, 384.0f, 0.0f, 256.0f),
		float((m_Game->GetScreenWidth() / 2) - 440 * (m_Game->GetScreenHeight() / 720.0f)),
		((float)m_Game->GetScreenHeight()) - 190 * (m_Game->GetScreenHeight() / 720.0f),
		0.0f, 0.75f, white );

#pragma endregion

	//HIGHLIGHTED BUTTONS --------------------------------------------------------------------------------------------
#pragma region Highlighted Buttons

	//m_WinElements[WIN_MAIN_HIGHLIGHTED_ELEMENT].Setup(m_Renderer, CAssetManager::GetInstance()->GetTexture(BUTTON_MAINMENU_HIGHLIGHTED), 
	//	RECTANGLE(0.0f, 256.0f, 0.0f, 64.0f),
	//	(float)(m_Game->GetScreenWidth() /2) - 384 * (m_Renderer->GetScreenHeight() / 720.0f),
	//	((float)m_Game->GetScreenHeight() / 2) +96 * (m_Renderer->GetScreenHeight() / 720.0f),
	//	0.0f, 1.0f, white);

	m_WinElements[WIN_CREDITS_HIGHLIGHTED_ELEMENT].Setup(m_Renderer, CAssetManager::GetInstance()->GetTexture(BUTTON_CREDITS_HIGHLIGHTED), 
		RECTANGLE(0.0f, 256.0f, 0.0f, 64.0f),
		m_WinElements[WIN_CREDITS_ELEMENT].GetPosX(),
		m_WinElements[WIN_CREDITS_ELEMENT].GetPosY(),
		0.0f, 1.0f, white);

#pragma endregion

	// For reticle
	Vec3f retPos = { m_Game->GetScreenWidth() / 2.0f - 50.0f, m_Game->GetScreenHeight() / 2.0f - 50.0f, 0.0f };
	m_reticle.Setup(m_Renderer, CAssetManager::GetInstance()->GetTexture(G_RETICULE), RECTANGLE(0.0f, 32, 0.0f, 32), 0.0f, 0.0f, 0.0f, 1.0f, white);

}