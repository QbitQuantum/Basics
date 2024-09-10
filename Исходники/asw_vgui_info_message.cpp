CASW_VGUI_Info_Message::CASW_VGUI_Info_Message( vgui::Panel *pParent, const char *pElementName, C_ASW_Info_Message* pMessage ) 
:	vgui::Panel( pParent, pElementName ),
	CASW_VGUI_Ingame_Panel()
{	
	//input->MouseEvent(0, false);	// unclick all our mouse buttons when this panel pops up (so firing doesn't get stuck on)

	if (g_hCurrentInfoPanel.Get())
	{
		g_hCurrentInfoPanel->MarkForDeletion();
		g_hCurrentInfoPanel->SetVisible(false);
	}
	g_hCurrentInfoPanel = this;
	m_hMessage = pMessage;
	for (int i=0;i<4;i++)
	{
		m_pLine[i] = new vgui::WrappedLabel(this, "InfoMessageLabel", "");
		m_pLine[i]->SetContentAlignment(vgui::Label::a_northwest);
		m_pLine[i]->SetMouseInputEnabled(false);
	}	
	m_pOkayButton = new ImageButton(this, "OkayButton", "#asw_close");
	m_pOkayButton->AddActionSignalTarget(this);
	KeyValues *msg = new KeyValues("Command");	
	msg->SetString("command", "OkayButton");
	m_pOkayButton->SetCommand(msg);

	m_pMessageImage = new vgui::ImagePanel(this, "MessageImage");
	m_pMessageImage->SetVisible(false);
	m_pMessageImage->SetShouldScaleImage(true);
	m_szImageName[0] = '\0';
	
	if (ShouldAddLogButton())
	{
		m_pLogButton = new ImageButton(this, "LogButton", "#asw_message_log");
		m_pLogButton->AddActionSignalTarget(this);
		KeyValues *msg = new KeyValues("Command");	
		msg->SetString("command", "MessageLog");
		m_pLogButton->SetCommand(msg);
	}
	else
	{
		Msg("  so not adding it\n");
		m_pLogButton = NULL;
	}

	// find use key bind	
	char lkeybuffer[12];
	Q_snprintf(lkeybuffer, sizeof(lkeybuffer), "%s", ASW_FindKeyBoundTo("+use"));
	Q_strupr(lkeybuffer);

	// copy the found key into wchar_t format (localize it if it's a token rather than a normal keyname)
	wchar_t keybuffer[24];
	if (lkeybuffer[0] == '#')
	{
		const wchar_t *pLocal = g_pVGuiLocalize->Find(lkeybuffer);
		if (pLocal)
			wcsncpy(keybuffer, pLocal, 24);
		else
			g_pVGuiLocalize->ConvertANSIToUnicode(lkeybuffer, keybuffer, sizeof(keybuffer));
	}
	else
		g_pVGuiLocalize->ConvertANSIToUnicode(lkeybuffer, keybuffer, sizeof(keybuffer));

	// look up close text localised
	const wchar_t *pLocal = g_pVGuiLocalize->Find("#asw_close");
	
	if (pLocal)
	{
		// join use key and close text together
		wchar_t buffer[ 256 ];
		g_pVGuiLocalize->ConstructString( buffer, sizeof(buffer), g_pVGuiLocalize->Find("#asw_use_icon_format"), 2, keybuffer, pLocal );
		// set label
		m_pOkayButton->SetText(buffer);
	}

	if (GetControllerFocus())
	{
		GetControllerFocus()->AddToFocusList(m_pOkayButton);
		GetControllerFocus()->SetFocusPanel(m_pOkayButton);
		if (m_pLogButton)
		{
			GetControllerFocus()->AddToFocusList(m_pLogButton);
		}
	}

	m_bClosingMessage = false;	
	
	CLocalPlayerFilter filter;

	// check for a special sound in the info message
	const char *pszSound = pMessage ? pMessage->GetSound() : NULL;	
	if (pszSound && Q_strlen(pszSound) > 0)
	{
		StopInfoMessageSound();

		EmitSound_t ep;
		ep.m_pSoundName = pszSound;
		ep.m_flVolume = 1.0f;
		ep.m_nPitch = PITCH_NORM;
		ep.m_SoundLevel = SNDLVL_NONE;
		ep.m_nChannel = CHAN_STATIC;

		C_BaseEntity::EmitSound( filter, SOUND_FROM_LOCAL_PLAYER, ep ); 
		g_LastInfoSoundGUID = enginesound->GetGuidForLastSoundEmitted();
	}

	UpdateMessage();

	SetAlpha(0);
	vgui::GetAnimationController()->RunAnimationCommand(this, "Alpha", 255, 0.0f, 0.3f, vgui::AnimationController::INTERPOLATOR_LINEAR);	

	SetKeyBoardInputEnabled(true);
	SetMouseInputEnabled(true);
	RequestFocus();

	ASWInput()->SetCameraFixed( true );

	g_asw_iGUIWindowsOpen++;		
}