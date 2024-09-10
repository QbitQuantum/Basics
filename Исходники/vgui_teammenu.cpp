// Creation
CTeamMenuPanel::CTeamMenuPanel(int iTrans, int iRemoveMe, int x, int y, int wide, int tall)
    : CMenuPanel(iTrans, iRemoveMe, x, y, wide, tall)
{
	// Get the scheme used for the Titles
	CSchemeManager *pSchemes = gViewPort->GetSchemeManager();

	// schemes
	SchemeHandle_t hTitleScheme    = pSchemes->getSchemeHandle("Title Font");
	SchemeHandle_t hTeamWindowText = pSchemes->getSchemeHandle("Briefing Text");
	SchemeHandle_t hTeamInfoText   = pSchemes->getSchemeHandle("Team Info Text");

	// get the Font used for the Titles
	Font *pTitleFont = pSchemes->getFont(hTitleScheme);
	int   r, g, b, a;

	// Create the title
	Label *pLabel = new Label("", TEAMMENU_TITLE_X, TEAMMENU_TITLE_Y);
	pLabel->setParent(this);
	pLabel->setFont(pTitleFont);
	pSchemes->getFgColor(hTitleScheme, r, g, b, a);
	pLabel->setFgColor(r, g, b, a);
	pSchemes->getBgColor(hTitleScheme, r, g, b, a);
	pLabel->setBgColor(r, g, b, a);
	pLabel->setContentAlignment(vgui::Label::a_west);
	pLabel->setText("%s", gHUD.m_TextMessage.BufferedLocaliseTextString("#Title_SelectYourTeam"));

	// Create the Info Window
	m_pTeamWindow = new CTransparentPanel(255, TEAMMENU_WINDOW_X, TEAMMENU_WINDOW_Y, TEAMMENU_WINDOW_SIZE_X, TEAMMENU_WINDOW_SIZE_Y);
	m_pTeamWindow->setParent(this);
	m_pTeamWindow->setBorder(new LineBorder(Color(255 * 0.7, 170 * 0.7, 0, 0)));

	// Create the Map Name Label
	m_pMapTitle = new Label("", TEAMMENU_WINDOW_TITLE_X, TEAMMENU_WINDOW_TITLE_Y);
	m_pMapTitle->setFont(pTitleFont);
	m_pMapTitle->setParent(m_pTeamWindow);
	pSchemes->getFgColor(hTitleScheme, r, g, b, a);
	m_pMapTitle->setFgColor(r, g, b, a);
	pSchemes->getBgColor(hTitleScheme, r, g, b, a);
	m_pMapTitle->setBgColor(r, g, b, a);
	m_pMapTitle->setContentAlignment(vgui::Label::a_west);

	// Create the Scroll panel
	m_pScrollPanel = new CTFScrollPanel(TEAMMENU_WINDOW_TEXT_X, TEAMMENU_WINDOW_TEXT_Y, TEAMMENU_WINDOW_SIZE_X - (TEAMMENU_WINDOW_TEXT_X * 2), TEAMMENU_WINDOW_TEXT_SIZE_Y);
	m_pScrollPanel->setParent(m_pTeamWindow);
	m_pScrollPanel->setScrollBarVisible(false, false);

	// Create the Map Briefing panel
	m_pBriefing = new TextPanel("", 0, 0, TEAMMENU_WINDOW_SIZE_X - TEAMMENU_WINDOW_TEXT_X, TEAMMENU_WINDOW_TEXT_SIZE_Y);
	m_pBriefing->setParent(m_pScrollPanel->getClient());
	m_pBriefing->setFont(pSchemes->getFont(hTeamWindowText));
	pSchemes->getFgColor(hTeamWindowText, r, g, b, a);
	m_pBriefing->setFgColor(r, g, b, a);
	pSchemes->getBgColor(hTeamWindowText, r, g, b, a);
	m_pBriefing->setBgColor(r, g, b, a);

	m_pBriefing->setText(gHUD.m_TextMessage.BufferedLocaliseTextString("#Map_Description_not_available"));

	// Team Menu buttons
	for(int i = 1; i <= 5; i++)
	{
		char sz[256];

		int iYPos = TEAMMENU_TOPLEFT_BUTTON_Y + ((TEAMMENU_BUTTON_SIZE_Y + TEAMMENU_BUTTON_SPACER_Y) * i);

		// Team button
		m_pButtons[i] = new CommandButton("", TEAMMENU_TOPLEFT_BUTTON_X, iYPos, TEAMMENU_BUTTON_SIZE_X, TEAMMENU_BUTTON_SIZE_Y, true);
		m_pButtons[i]->setParent(this);
		m_pButtons[i]->setContentAlignment(vgui::Label::a_west);
		m_pButtons[i]->setVisible(false);

		// AutoAssign button uses special case
		if(i == 5)
		{
			m_pButtons[5]->setBoundKey('5');
			m_pButtons[5]->setText(gHUD.m_TextMessage.BufferedLocaliseTextString("#Team_AutoAssign"));
			m_pButtons[5]->setVisible(true);
		}

		// Create the Signals
		sprintf(sz, "jointeam %d", i);
		m_pButtons[i]->addActionSignal(new CMenuHandler_StringCommandWatch(sz, true));
		m_pButtons[i]->addInputSignal(new CHandler_MenuButtonOver(this, i));

		// Create the Team Info panel
		m_pTeamInfoPanel[i] = new TextPanel("", TEAMMENU_WINDOW_INFO_X, TEAMMENU_WINDOW_INFO_Y, TEAMMENU_WINDOW_SIZE_X - TEAMMENU_WINDOW_INFO_X, TEAMMENU_WINDOW_SIZE_X - TEAMMENU_WINDOW_INFO_Y);
		m_pTeamInfoPanel[i]->setParent(m_pTeamWindow);
		m_pTeamInfoPanel[i]->setFont(pSchemes->getFont(hTeamInfoText));
		m_pTeamInfoPanel[i]->setFgColor(iTeamColors[i % iNumberOfTeamColors][0],
		                                iTeamColors[i % iNumberOfTeamColors][1],
		                                iTeamColors[i % iNumberOfTeamColors][2],
		                                0);
		m_pTeamInfoPanel[i]->setBgColor(0, 0, 0, 255);
	}

	// Create the Cancel button
	m_pCancelButton = new CommandButton(CHudTextMessage::BufferedLocaliseTextString("#Menu_Cancel"), TEAMMENU_TOPLEFT_BUTTON_X, 0, TEAMMENU_BUTTON_SIZE_X, TEAMMENU_BUTTON_SIZE_Y);
	m_pCancelButton->setParent(this);
	m_pCancelButton->addActionSignal(new CMenuHandler_TextWindow(HIDE_TEXTWINDOW));

	// Create the Spectate button
	m_pSpectateButton = new SpectateButton(CHudTextMessage::BufferedLocaliseTextString("#Menu_Spectate"), TEAMMENU_TOPLEFT_BUTTON_X, 0, TEAMMENU_BUTTON_SIZE_X, TEAMMENU_BUTTON_SIZE_Y, true);
	m_pSpectateButton->setParent(this);
	m_pSpectateButton->addActionSignal(new CMenuHandler_StringCommand("spectate", true));
	m_pSpectateButton->setBoundKey('6');
	m_pSpectateButton->addInputSignal(new CHandler_MenuButtonOver(this, 6));

	Initialize();
}